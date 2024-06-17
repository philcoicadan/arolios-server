/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/Login.h>
#include <drogon/HttpAppFramework.h>
#include <util/String.h>
#include <svru/Request.h>
#include <svru/Response.h>


using namespace arolios;
using namespace arolios::filter;
void Login::doFilter(const drogon::HttpRequestPtr &req,
                         drogon::FilterCallback &&fcb,
                         drogon::FilterChainCallback &&fccb)
{
      

    if (req->session()->find("token")) {
        
        std::string session_token = req->session()->get<std::string>("token");
        std::string header = req->getHeader("Authorization");
        auto std_vec = util::String::split(header,' ');
        if (std_vec.size() > 1) {
            std::string req_token = std_vec[1];
            

            if ( session_token == req_token ) {
                //Passed
                fccb();
                return;
            }
        }
    }
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(drogon::k500InternalServerError);
    svru::Response::add_allow_headers (res, req) ;

    fcb(res);
}
