/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/RAC_default_app.h>
#include <common/User.h>
#include <drogon/HttpAppFramework.h>
#include <common/Singleton.h>
#include <common/App_info.h>
#include <appcfg/App.h>
#include <svru/Request.h>
#include <svru/Response.h>


using namespace arolios;
using namespace arolios::filter;



void RAC_default_app::doFilter(const drogon::HttpRequestPtr &req,
                         drogon::FilterCallback &&fcb,
                         drogon::FilterChainCallback &&fccb)
{
        
         
    auto app_info = common::Singleton<common::App_info>::instance().object();

    if ( app_info->app() == app_info->default_app() ) {
        //Passed
        fccb();
        return;
    }
 
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(drogon::k500InternalServerError);
    svru::Response::add_allow_headers (res, req) ;

    fcb(res);
} 
