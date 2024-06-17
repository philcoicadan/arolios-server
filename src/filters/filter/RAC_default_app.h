/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpFilter.h>

namespace arolios {


namespace filter {

class RAC_default_app : public drogon::HttpFilter<RAC_default_app> {
    
    
    virtual void doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) override;
    
};

}
}

