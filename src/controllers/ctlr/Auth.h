/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>
#include <ctlr/Nothing.h>
#include <filter/RAC_util.h>

namespace arolios {

using namespace drogon;
namespace ctlr
{
class Auth:public drogon::HttpController<Auth>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ctlr::Nothing::options, "/login", Options, "arolios::filter::Post_option");
    ADD_METHOD_TO(ctlr::Auth::login, "/login", drogon::Post);
    
    ADD_METHOD_TO(ctlr::Nothing::options, "/logout", Options, "arolios::filter::Post_option");
    ADD_METHOD_TO(ctlr::Auth::logout, "/logout", drogon::Post);
    
    ADD_METHOD_TO(ctlr::Nothing::options, "/password", Options, "arolios::filter::Post_option");
    ADD_METHOD_TO(ctlr::Auth::change_password, "/password", drogon::Post, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

    METHOD_LIST_END

    void login (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void logout (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void change_password (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
}
}

