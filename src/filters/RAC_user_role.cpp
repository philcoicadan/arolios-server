/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/RAC_user_role.h>
#include <common/User.h>
#include <drogon/HttpAppFramework.h>
#include <common/Singleton.h>
#include <common/UAC_info.h>
#include <svru/Request.h>
#include <svru/Response.h>


using namespace arolios;
using namespace arolios::filter;

template <int TR> RAC_user_role<TR>::RAC_user_role () : required_role_ (static_cast<common::User_role>(TR)) {
}

template <int TR> void RAC_user_role<TR>::doFilter(const drogon::HttpRequestPtr &req,
                         drogon::FilterCallback &&fcb,
                         drogon::FilterChainCallback &&fccb)
{
    user_ac_ptr_ = drogon::app().getPlugin<plugin::User_access_control>();

    std::shared_ptr<common::User> user = req->session()->get<std::shared_ptr<common::User>>("user");
   
    if ( user_ac_ptr_->check_role(user->app_role(), required_role_ )) {
        //Passed
        fccb();
        return;
    }
 
    //Check failed
   
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(drogon::k500InternalServerError);
    svru::Response::add_allow_headers (res, req) ;

    fcb(res);
} 

namespace arolios::filter {
    template class RAC_user_role<1>;
    template class RAC_user_role<2>;
    template class RAC_user_role<3>;
}