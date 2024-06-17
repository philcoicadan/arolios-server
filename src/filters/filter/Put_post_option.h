/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <filter/Option.h>

namespace arolios {


namespace filter {
class Put_post_option : public drogon::HttpFilter<Put_post_option>, public Option {
public:

    Put_post_option() ;
    virtual void doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) override;

};

}

}

