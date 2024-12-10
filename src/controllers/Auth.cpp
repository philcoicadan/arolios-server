/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include "exception/Exceptions.h"
#include <ctlr/Auth.h>
#include <drogon/HttpAppFramework.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <drogon/HttpTypes.h>
#include <plugin/User_access_control.h>
#include <common/User.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <svru/About.h>
#include <mttr/User_change_password.h>
#include <appcfg/App.h>
#include <ctime>

using namespace arolios;
using namespace arolios::ctlr;

void Auth::login ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback ) {

  try {
    auto app_ptr = common::Singleton<common::App_info>::instance().object();
    auto user_ac = common::Singleton<common::UAC_info>::instance().object();

    auto input = req->getJsonObject();
    if (input) {
      auto identifier = (*input)["username"].asString();
      auto pwd = (*input)["password"].asString();

      const auto user = user_ac->retrieve(identifier, pwd);
      if (user) {

        const auto token = drogon::utils::getUuid();

        req->session()->insert("token", token);
        req->session()->insert("user", user);

        const std::time_t now = std::time(nullptr);

        std::cout << "time: " << std::put_time(std::localtime(&now), "%x %X")
                  << ", user: " << user->identifier() << " logged in"
                  << std::endl;

        Json::Value ret;
        ret["token"] = token;

        ret["user"] = Json::Value(Json::objectValue);
        ret["user"]["identifier"] = user->identifier();
        ret["user"]["role"] = user_ac->string_cast(user->app_role());

        ret["app"] = Json::Value(Json::objectValue);
        ret["app"]["name"] = app_ptr->app()->name();
        ret["app"]["isDefault"] =
            (app_ptr->app()->id() == app_ptr->default_app_id());
        ret["app"]["defaultLanguage"] = app_ptr->default_language()->code();

        ret["about"] = svru::About::notice_text();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        svru::Response::add_allow_headers(resp, req);

        callback(resp);
        return;

      } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Username and/or Password not valid");
        resp->setStatusCode(drogon::k400BadRequest);
        svru::Response::add_allow_headers(resp, req);

        callback(resp);
        return;
      }

    } else {
      auto resp = HttpResponse::newHttpResponse();

      resp->setStatusCode(drogon::k400BadRequest);
      svru::Response::add_allow_headers(resp, req);

      callback(resp);
      return;
    }
  } catch (const exception::Input_error &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k400BadRequest);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  } catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}

void Auth::logout ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback ) {

 try {   
    auto user = req->session()->get<std::shared_ptr<common::User>>("user");
    if (user != nullptr) {
  
        const std::time_t now = std::time(nullptr);
                
        std::cout << "time: " << std::put_time(std::localtime(&now), "%x %X") << ", user: " << user->identifier() << " logged out" << std::endl;
    }

    req->session()->clear();


    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode ( k200OK );
    svru::Response::add_allow_headers (resp, req) ;

    callback ( resp );
    return ;

  } catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }

}

void Auth::change_password (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) {
    
    

    try {

        std::shared_ptr<common::User> user = req->session()->get<std::shared_ptr<common::User>> ( "user" );
        auto resp = HttpResponse::newHttpResponse();

        if ( user ) {
            auto json_ptr = req->jsonObject() ;
            if (json_ptr == nullptr) {
              throw exception::Input_error("Data missing");
            }

            mttr::User_change_password ucp ( user, *json_ptr );
            ucp.execute ();

            if ( ucp.return_code () == qry::Return_code::OK ) {
                resp->setStatusCode ( drogon::k200OK );
                resp->setContentTypeCode ( CT_TEXT_HTML );
                resp->setBody ( "User password updated " );
            } else {
                resp->setStatusCode ( drogon::k400BadRequest );
                resp->setContentTypeCode ( CT_TEXT_HTML );
                resp->setBody ( "User password updating failed " );
            }
        } else {
            resp->setStatusCode ( k400BadRequest );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "User not found " );
        }

        svru::Response::add_allow_headers ( resp, req ) ;


        callback ( resp );
        return;
    }
    catch ( const exception::Input_error&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
        resp->setStatusCode ( k400BadRequest);
        svru::Response::add_allow_headers ( resp, req ) ;

        callback ( resp );
        return;
    }
    catch ( const std::exception&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers ( resp, req ) ;

        callback ( resp );
        return;
    }
}
