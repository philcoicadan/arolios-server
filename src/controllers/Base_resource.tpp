/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Base_resource.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <util/String.h>
#include <qry/Util.h>
#include <qry/Return_code.h>
#include <drogon/HttpAppFramework.h>
#include <common/Object_model_info.h>
#include <common/App_info.h>
#include <common/Singleton.h>









using namespace arolios;
using namespace arolios::ctlr;


template < typename TC> void Base_resource::create(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const {

    try {



        auto resp = HttpResponse::newHttpResponse();
        auto json_ptr = req->jsonObject() ;

        TC ac ( *json_ptr );
        ac.execute ();

        if ( ac.return_code () == qry::Return_code::OK ) {

            resp = HttpResponse::newHttpJsonResponse ( ac.return_json() );
        } else {
            resp->setStatusCode ( k500InternalServerError );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Resource creation failed " );
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
    

template <typename TL> void Base_resource::list (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction,  std::string&& p_lang  ) const {

    try {

       auto app_ptr = common::Singleton<common::App_info>::instance().object();
       
        auto lang = app_ptr->get_language_by_code(p_lang);

        const auto list_params = svru::Request::check_list_params (p_sort, p_direction,p_limit,p_offset, true);
       
       
        

        auto resp = HttpResponse::newHttpResponse();

        TL al ( list_params.offset_, list_params.limit_, list_params.sort_, list_params.direction_, lang) ;
        al.execute ();

        if ( al.return_code () == qry::Return_code::OK ) {
            const Json::Value & json = al.return_json();

            resp = HttpResponse::newHttpJsonResponse ( json );

        } else {
            resp->setStatusCode ( k500InternalServerError );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Resource list failed " );
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
};

template <typename TU> void Base_resource::read(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_elem_id, std::string&& p_usage,  std::string&& p_lang ) const{

            auto app_ptr = common::Singleton<common::App_info>::instance().object();

            auto elem_id = svru::Request::check_element_id (p_elem_id);

    
        
        try {


        auto lang = app_ptr->get_language_by_code(util::String::standardize (p_lang));
        
        auto && usage = ( p_usage.length() == 0 ) ? "ro" : util::String::standardize ( p_usage );
        if ( usage != "ro" && usage != "rfu" ) {
            std::cout << "WARNING: read mode " << usage << "is unknown, default mode (read only) is applied" << std::endl;
            usage = "ro";
        }

        qry::Util::Read_mode read_mode = qry::Util::convert_read_mode ( usage );


        auto resp = HttpResponse::newHttpResponse();

        TU ar ( elem_id, read_mode, lang);
        ar.execute ();

        if ( ar.return_code () == qry::Return_code::OK ) {
                const Json::Value & json = ar.return_json();

                resp = HttpResponse::newHttpJsonResponse ( json );

        } else {
            resp->setStatusCode ( k500InternalServerError );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Resource reading failed " );
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
};


template <typename TU> void Base_resource::update(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_elem_id) const{

            auto elem_id = svru::Request::check_element_id (p_elem_id);

    
        
        try {



        auto resp = HttpResponse::newHttpResponse();
        auto json_ptr = req->jsonObject() ;
        const int upd_count = json_ptr->get("upd_count",0).asInt();
        TU au ( elem_id, *json_ptr , upd_count);
        au.execute ();

        if ( au.return_code () == qry::Return_code::OK ) {
            resp->setStatusCode ( k202Accepted );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "App updated " );
        } else {
            resp->setStatusCode ( k422UnprocessableEntity );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "App updating failed " );
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
};


template <typename TD> void Base_resource::deletion (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_elem_id) const{
    

    auto elem_id = svru::Request::check_element_id (p_elem_id);

    
          
    try {



        auto resp = HttpResponse::newHttpResponse();
        TD ad (elem_id);
        ad.execute ();

        if ( ad.return_code () == qry::Return_code::OK ) {
            resp->setStatusCode ( k202Accepted );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Resource deleted " );
        } else {
            resp->setStatusCode ( k422UnprocessableEntity );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Resource deletion failed " );
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

