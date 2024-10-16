/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Classifiers.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <common/Object_model_info.h>
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/utils/Utilities.h>
#include <json/json.h>
#include <qry/Classifier_properties_list.h>
#include <qry/Classifier_instances_list.h>
#include <qry/Classifiers_list.h>
#include <qry/Instance_filter.h>
#include <util/String.h>
#include <qry/Return_code.h>
#include <mttr/Classifier_instance_factory.h>
#include <mttr/Classifier_instance_create.h>
#include <memory>
#include <svru/Request.h>
#include <svru/Response.h>
#include <svru/Request.h>
#include <svru/Response.h>


using namespace arolios;
using namespace arolios::ctlr;

template <typename T>
void Classifiers<T>::list_instances(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_elem, std::string &&p_offset, std::string &&p_limit,
    std::string &&p_sort, std::string &&p_direction, std::string &&p_filters,
    std::string &&p_prop_list, std::string &&p_lang) const {



  try {
    auto app_ptr = common::Singleton<common::App_info>::instance().object();

    auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();


    auto lang = app_ptr->get_language_by_code(util::String::standardize(p_lang));

   

    auto list_params =
        svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);

    auto prop_list = svru::Request::check_prop_list_mode(p_prop_list);

  

    auto filters = qry::Instance_filter::make_fts_filters(p_filters);

    // add filter to select only active (non-deleted) instances
    const std::shared_ptr<const qry::Instance_filter> td_filter =
        std::make_shared<qry::Instance_filter>("trashed_date", "=", "'epoch'");
    filters.push_back(td_filter);

    auto resp = HttpResponse::newHttpResponse();


    const std::shared_ptr<T> elem = svru::Request::is_id( p_elem) ?
        om_ptr->find_domain_element_by_id<T> (p_elem):
        app_ptr->find_domain_element_by_full_name<T>(p_elem);


    if (elem) {
     
      qry::Classifier_instances_list<T> q(
          elem, list_params.offset_, list_params.limit_,
          list_params.sort_, list_params.direction_, filters, prop_list, lang);

      q.execute();

      if (q.return_code() == qry::Return_code::OK) {
        const Json::Value &json = q.return_json();

        resp = HttpResponse::newHttpJsonResponse(json);


      } else {
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody("Instances list failed ");
      }
    } else {
      resp->setStatusCode(k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Classifier not found ");
    }

    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  } 
  catch (const exception::Input_error &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k400BadRequest);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  } 
  catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
     
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}

template <typename T>
void Classifiers<T>::create_instance(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_elem) const {



  try {
    auto app_ptr = common::Singleton<common::App_info>::instance().object();

    auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();

    const std::shared_ptr<T> elem = svru::Request::is_id( p_elem) ?
        om_ptr->find_domain_element_by_id<T> (p_elem):
        app_ptr->find_domain_element_by_full_name<T>(p_elem);


    auto resp = HttpResponse::newHttpResponse();
    

    auto json_ptr = req->jsonObject();

    if (elem) {
      if (!elem->is_abstract()) {

        auto ic = mttr::Classifier_instance_factory::instance().make_create(
            elem, *json_ptr);

        if (ic) {
          ic->execute();

          if (ic->return_code() == qry::Return_code::OK) {
            resp = HttpResponse::newHttpJsonResponse(ic->return_json());
          } else {
            resp->setStatusCode(drogon::k400BadRequest);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody("Classifier instance creation failed ");
          }
        } else {
          resp->setStatusCode(k500InternalServerError);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Classifier without relational object ");
        }
      } else {
        resp->setStatusCode(k400BadRequest);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody("Classifier is abstract, creation not applicable");
      }

    } else {
      resp->setStatusCode(k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Classifier not found ");
    }

    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  } 
  catch (const exception::Input_error &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k400BadRequest);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  } 
  catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
     
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}

template <typename T>
void Classifiers<T>::list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_offset, std::string &&p_limit, std::string &&p_sort,
    std::string &&p_direction, std::string &&p_lang) const {





  try {

    const auto app_ptr = common::Singleton<common::App_info>::instance().object();

    auto lang = app_ptr->get_language_by_code(util::String::standardize(p_lang));

    auto list_params =
        svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);

     

    auto resp = HttpResponse::newHttpResponse();

    const auto domains = app_ptr->list_user_domains();

    qry::Classifiers_list<T> al(domains, list_params.offset_,
                                list_params.limit_, list_params.sort_,
                                list_params.direction_, lang);
    al.execute();

    if (al.return_code() == qry::Return_code::OK) {
      const Json::Value &json = al.return_json();

      resp = HttpResponse::newHttpJsonResponse(json);


    } else {
      resp->setStatusCode(drogon::k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("List of classifiers failed ");
    }
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
    catch (const exception::Input_error &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k400BadRequest);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
  catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
     
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}

template <typename T>
void Classifiers<T>::list_properties(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_elem, std::string &&p_offset, std::string &&p_limit,
    std::string &&p_sort, std::string &&p_direction, std::string &&p_context,
    std::string &&p_lang) const {



  try {
    auto app_ptr = common::Singleton<common::App_info>::instance().object();

    auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();

    const auto lang = app_ptr->get_language_by_code(p_lang);

    const auto list_params =
        svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);

        auto ctx = p_context;
    if (ctx.empty()) {
      ctx = "IDS";
    } else {
      std::transform(
          ctx.begin(), ctx.end(), ctx.begin(),
          [](unsigned char c) -> unsigned char { return std::toupper(c); });
    }

    if (ctx != "IDS" && ctx != "LIST" && ctx != "READ" && ctx != "CREATE" &&
        ctx != "UPDATE") {
      std::cout << "WARNING: context " << ctx
                << "is unknown, default mode (ids) is applied" << std::endl;;
      ctx = "IDS";
    }

 

    auto resp = HttpResponse::newHttpResponse();
    

    const std::shared_ptr<T> elem = svru::Request::is_id( p_elem) ?
        om_ptr->find_domain_element_by_id<T> (p_elem):
        app_ptr->find_domain_element_by_full_name<T>(p_elem);


    if (elem) {


      qry::Classifier_properties_list q(
          elem, list_params.offset_, list_params.limit_,
          list_params.sort_, list_params.direction_, ctx, lang);

      q.execute();

      if (q.return_code() == qry::Return_code::OK) {
        const Json::Value &json = q.return_json();

        resp = HttpResponse::newHttpJsonResponse(json);


      } else {
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody("Properties list failed ");
      }
    } else {
      resp->setStatusCode(k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Classifier not found ");
    }

    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
  catch (const exception::Input_error &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k400BadRequest);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
  catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
     
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}
