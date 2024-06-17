/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Enumerations.h>
#include <json/json.h>
#include <common/Object_model_info.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <drogon/utils/Utilities.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpAppFramework.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <util/String.h>
#include <qry/Return_code.h>
#include <qry/Enumeration_values_list.h>
#include <qry/Classifiers_list.h>
#include <omm/Enumeration.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <svru/Request.h>
#include <svru/Response.h>









using namespace arolios;
using namespace arolios::ctlr;



void Enumerations::list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string &&p_offset, std::string &&p_limit, std::string &&p_sort,
    std::string &&p_direction, std::string &&p_lang) const {

  


  const auto app_ptr = common::Singleton<common::App_info>::instance().object();

  try {


    auto lang = app_ptr->get_language_by_code(util::String::standardize(p_lang));

    auto list_params =
        svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);

        

        auto resp = HttpResponse::newHttpResponse();

    const auto domains = app_ptr->list_user_domains();

    qry::Classifiers_list<omm::Enumeration> al( domains, list_params.offset_,
                                list_params.limit_, list_params.sort_,
                                list_params.direction_, lang);
    al.execute();

    if (al.return_code() == qry::Return_code::OK) {
      const Json::Value &json = al.return_json();

      resp = HttpResponse::newHttpJsonResponse(json);


    } else {
      resp->setStatusCode(k500InternalServerError);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("List of Enumerations failed ");
    }
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

void Enumerations::values(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_enum, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction, std::string&& p_lang ) const {

    

    auto app_ptr = common::Singleton<common::App_info>::instance().object();
    
    try {
        auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();
        auto lang = app_ptr->get_language_by_code(p_lang);

        const auto list_params =
            svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);
        
 

        auto resp = HttpResponse::newHttpResponse();
       
        const std::shared_ptr<omm::Enumeration> enum_ptr = svru::Request::is_id( p_enum) ?
        om_ptr->find_domain_element_by_id<omm::Enumeration> (p_enum):
        app_ptr->find_domain_element_by_full_name<omm::Enumeration>(p_enum);
       
        if (enum_ptr ) {
            qry::Enumeration_values_list  evl ( enum_ptr, list_params.offset_, list_params.limit_,
          list_params.sort_, list_params.direction_, lang) ;
       
            evl.execute (); 
             
            if ( evl.return_code () == qry::Return_code::OK ) {
                const Json::Value & json = evl.return_json();

                resp = HttpResponse::newHttpJsonResponse ( json );


            } else {
                resp->setStatusCode ( k500InternalServerError );
                resp->setContentTypeCode ( CT_TEXT_HTML );
                resp->setBody ( "Values list failed " );
            }
        } else {
            resp->setStatusCode ( k400BadRequest );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Enumeration not found " );
        }

        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    }
    catch ( const std::exception&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
         
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    }
    
}

