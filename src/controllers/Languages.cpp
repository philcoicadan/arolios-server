/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Languages.h>
#include <drogon/HttpTypes.h>
#include <json/json.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <common/Object_model_info.h>
#include <util/String.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <qry/Languages_list.h>
#include <qry/Instance_filter.h>




using namespace arolios;
using namespace arolios::ctlr;

void Languages::list ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_filters) const {
    
  
            
    const auto app_ptr = common::Singleton<common::App_info>::instance().object();

    try {

        
        std::string sort = "code";


        std::string dir = "ASC";

        std::string offset = "";
        std::string limit = "";

        auto filters = qry::Instance_filter::make_language_filters(p_filters);
        
        
        auto resp = HttpResponse::newHttpResponse();
        
         qry::Languages_list ll  ( offset, limit, sort, dir, filters, app_ptr->default_language());
        ll.execute();

        if ( ll.return_code () == qry::Return_code::OK ) {
            const Json::Value & json = ll.return_json();

            resp = HttpResponse::newHttpJsonResponse ( json );


        } else {
            resp->setStatusCode ( drogon::k422UnprocessableEntity );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "languages list failed " );
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
