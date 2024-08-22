/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Nothing.h>
#include <svru/Request.h>
#include <svru/Response.h>


using namespace arolios;
using namespace arolios::ctlr;

void Nothing::options ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback ) const {
    
    common_options (req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
    
}

void Nothing::options_1 ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback , std::string&& p_app_name) const {
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

 void Nothing::options_2 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_3 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3 ) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_4 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4 ) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_5 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_6 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_7 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_8 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_9 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8, std::string&& p_str9 ) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_10 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8, std::string&& p_str9, std::string&& p_str10 ) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}

void Nothing::options_11 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8, std::string&& p_str9, std::string&& p_str10, std::string&& p_str11 ) const{
    
    Nothing::common_options( req, (std::function<void ( const HttpResponsePtr & ) > &&)callback) ;
}


void Nothing::common_options (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) {

    // called only if the filter of OPTIONS request is badly called
    
        const auto & res = drogon::HttpResponse::newHttpResponse();
        res->setStatusCode(k500InternalServerError);
        svru::Response::add_allow_methods (res, req, "OPTIONS") ;

        callback ( res );
}
