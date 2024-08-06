/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Domains.h>
#include <drogon/HttpTypes.h>
#include <json/json.h>
#include <qry/Domains_list.h>
#include <qry/Classifiers_list.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <common/Object_model_info.h>
#include <util/String.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <svru/Request.h>
#include <svru/Response.h>




using namespace arolios;
using namespace arolios::ctlr;



void Domains::list(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback , std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction, std::string&& p_lang ) const {

	
            
    const auto app_ptr = common::Singleton<common::App_info>::instance().object();

    try {
 
        auto lang = app_ptr->get_language_by_code(util::String::standardize(p_lang));
        
        const auto list_params = svru::Request::check_list_params (p_sort, p_direction, p_limit, p_offset, false);
       
      
        auto resp = HttpResponse::newHttpResponse();


        qry::Domains_list dl  (
        list_params.offset_, list_params.limit_, list_params.sort_, list_params.direction_, lang);
        dl.execute();

        if ( dl.return_code () == qry::Return_code::OK ) {
            const Json::Value & json = dl.return_json();

            resp = HttpResponse::newHttpJsonResponse ( json );

        } else {
            resp->setStatusCode ( drogon::k422UnprocessableEntity );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Domains list failed " );
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



template <typename T> void Domains::list_classifiers(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_pk_name, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction, std::string&& p_lang ) const {

	
    
                
    const auto app_ptr = common::Singleton<common::App_info>::instance().object();

    try {
        auto lang = app_ptr->get_language_by_code(p_lang);
        
        const auto list_params = svru::Request::check_list_params (p_sort, p_direction, p_limit, p_offset, false);
        
       
        auto resp = HttpResponse::newHttpResponse();
        
        
        const std::shared_ptr<const omm::Package> pk = svru::Request::is_id(p_pk_name) ?
        app_ptr->find_domain_by_id( p_pk_name ) :
        app_ptr->find_domain_by_name( util::String::standardize ( p_pk_name ) );
        
        
        if ( pk ) {
            
            const std::vector<std::shared_ptr<const omm::Package>> pk_vec { pk } ;

            qry::Classifiers_list<T> cl ( pk_vec, list_params.offset_, list_params.limit_, list_params.sort_, list_params.direction_, lang);
            cl.execute();

            if ( cl.return_code () == qry::Return_code::OK ) {
                const Json::Value & json = cl.return_json();

                resp = HttpResponse::newHttpJsonResponse ( json );

            } else {
                resp->setStatusCode ( drogon::k422UnprocessableEntity );
                resp->setContentTypeCode ( CT_TEXT_HTML );
                resp->setBody ( "Domain elements list failed " );
            }

        } else {
            resp->setStatusCode ( k400BadRequest );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Domain not found " );
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

namespace arolios::ctlr {
template void Domains::list_classifiers<omm::Class>(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, std::string &&p_pk_name, std::string &&p_offset, std::string &&p_limit, std::string &&p_sort, std::string &&p_direction, std::string &&p_lang) const;
template void Domains::list_classifiers<omm::Association>(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, std::string &&p_pk_name, std::string &&p_offset, std::string &&p_limit, std::string &&p_sort, std::string &&p_direction, std::string &&p_lang) const;
template void Domains::list_classifiers<omm::Enumeration>(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, std::string &&p_pk_name, std::string &&p_offset, std::string &&p_limit, std::string &&p_sort, std::string &&p_direction, std::string &&p_lang) const;

}