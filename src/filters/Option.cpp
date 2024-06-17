/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/Option.h>
#include <drogon/HttpAppFramework.h>
#include <svru/Request.h>
#include <svru/Response.h>


using namespace arolios;
using namespace arolios::filter;
Option::Option( const std::string& p_requested_method) : requested_method_(p_requested_method) {}

void Option::filter(const drogon::HttpRequestPtr &req,
                         drogon::FilterCallback &&fcb,
                         drogon::FilterChainCallback &&fccb)
{
         

    //Edit your logic here

    if ( req->method() == drogon::Options ) {
        //Return the response
        const auto & res = drogon::HttpResponse::newHttpResponse();
        svru::Response::add_allow_methods (res, req, requested_method_) ;

        fcb ( res );
        return;
    }
    //Pass
    fccb();
    
}

