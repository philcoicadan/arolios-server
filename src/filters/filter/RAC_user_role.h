/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpFilter.h>
#include <plugin/User_access_control.h>
#include <common/User_role.h>

namespace arolios {



namespace filter {
    
template  <int TR> class RAC_user_role :  public drogon::HttpFilter<RAC_user_role<TR>>
{
  public:
    virtual void doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) override;
                        

    RAC_user_role()  ;

    
private:
    const plugin::User_access_control* user_ac_ptr_;
    common::User_role required_role_;
};

}
}

