/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Trash.h>
#include <drogon/HttpTypes.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <mttr/Classifier_instance_factory.h>
#include <mttr/Classifier_instance_eliminate.h>
#include <mttr/Classifier_instance_recover.h>
#include <mttr/Trash_empty.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <common/Object_model_info.h>
#include <qry/Trash_list.h>
#include <qry/Instance_filter.h>
#include <util/String.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <qry/Return_code.h>


using namespace arolios;
using namespace arolios::ctlr;

void Trash::list_instances(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_offset, std::string &&p_limit, std::string &&p_sort,
    std::string &&p_direction, std::string &&p_filters,
    std::string &&p_lang) const {




  try {
    auto app_ptr = common::Singleton<common::App_info>::instance().object();


    auto lang = app_ptr->get_language_by_code(p_lang);

    auto list_params =
        svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);

    

    const auto &filters = qry::Instance_filter::make_fts_filters(p_filters);

    auto resp = HttpResponse::newHttpResponse();

    qry::Trash_list q( list_params.offset_, list_params.limit_,
                      list_params.sort_, list_params.direction_, filters, lang);

    q.execute();

    if (q.return_code() == qry::Return_code::OK) {
      const Json::Value &json = q.return_json();

      resp = HttpResponse::newHttpJsonResponse(json);


    } else {
      resp->setStatusCode(drogon::k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Trash list failed ");
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

void Trash::recover_instance(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_trash_id) const {


  

  try {
    auto app_ptr = common::Singleton<common::App_info>::instance().object();

    auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();



    const auto [csf_id, row_id] =
        qry::Util::split_instance_id(p_trash_id);
   

    // lookup classifier

    auto csf = om_ptr->find_domain_element_by_id<omm::Classifier>(
        std::to_string(csf_id));

    auto resp = HttpResponse::newHttpResponse();

    auto json_ptr = req->jsonObject();

    if (csf) {
      const int upd_count = json_ptr->get("upd_count", 0).asInt();

      auto ir = mttr::Classifier_instance_factory::instance().make_recover(
          csf, p_trash_id, upd_count);
      if (ir) {
        ir->execute();

        if (ir->return_code() == qry::Return_code::OK) {
          resp->setStatusCode(drogon::k200OK);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Instance recovered ");
        } else {
          resp->setStatusCode(drogon::k400BadRequest);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Instance recovery failed ");
        }
      } else {
        resp->setStatusCode(k500InternalServerError);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody("Classifier without relational object ");
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

void Trash::eliminate_instance(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_trash_id) const {




  try {

    auto om_ptr =
        common::Singleton<common::Object_model_info>::instance().object();

    const auto [csf_id, row_id] = qry::Util::split_instance_id(p_trash_id);

    // lookup classifier

    auto csf = om_ptr->find_domain_element_by_id<omm::Classifier>(
        std::to_string(csf_id));

    auto resp = HttpResponse::newHttpResponse();

    auto json_ptr = req->jsonObject();

    if (csf) {
      const int upd_count = json_ptr->get("upd_count", 0).asInt();

      auto ie = mttr::Classifier_instance_factory::instance().make_eliminate(
          csf, p_trash_id, upd_count);
      if (ie) {
        ie->execute();

        if (ie->return_code() == qry::Return_code::OK) {
          resp->setStatusCode(drogon::k200OK);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Instance deleted definitively");
        } else {
          resp->setStatusCode(drogon::k400BadRequest);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Instance definitive deletion failed ");
        }
      } else {
        resp->setStatusCode(k500InternalServerError);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody("Classifier without relational object ");
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

void Trash::empty(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {

  


  try {


    auto resp = HttpResponse::newHttpResponse();

    mttr::Trash_empty tp;

    tp.execute();

    if (tp.return_code() == qry::Return_code::OK) {
      resp->setStatusCode(drogon::k200OK);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Trash emptying ended successfully");

    } else {
      resp->setStatusCode(drogon::k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Trash emptying failed ");
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
