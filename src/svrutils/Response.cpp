/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <svru/Request.h>
#include <svru/Response.h>
#include <util/String.h>
#include <drogon/HttpAppFramework.h>
#include <plugin/App_server.h>
#include <common/App_info.h>
#include <common/Singleton.h>


using namespace arolios;
using namespace arolios::svru;


void Response::add_allow_headers (const drogon::HttpResponsePtr& p_resp, const drogon::HttpRequestPtr& p_req) {
    
    const auto app_ptr = drogon::app().getPlugin<plugin::App_server>();
    const auto & origin_set = app_ptr->authorized_origins();
    
    const auto origin = p_req->getHeader("origin") ;
    if (!origin.empty()) {
        // origin is present => cross origin requests or same origin requestsfor POST,PUT,PATCH,DELETE,OPTIONS
        // check origin is in the authorized list
        auto search = origin_set.find(origin) ;
        if ( search != origin_set.end()) {
             p_resp->addHeader ( "Access-Control-Allow-Origin", origin );
        }
    
    } 

    p_resp->addHeader ( "Access-Control-Allow-Headers", "Origin, Authorization, Content-type" );
    p_resp->addHeader ( "Access-Control-Allow-Credentials", "true" );
}

void Response::add_allow_methods ( const drogon::HttpResponsePtr& p_resp, const drogon::HttpRequestPtr& p_req, const std::string& p_requested_method )  {

    const auto & app_ptr = common::Singleton<common::App_info>::instance().object();

    add_allow_headers (p_resp, p_req) ;

    p_resp->addHeader ( "Access-Control-Allow-Methods", p_requested_method );
}