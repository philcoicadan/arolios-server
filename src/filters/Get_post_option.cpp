/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/Get_post_option.h>

using namespace arolios;
using namespace arolios::filter;
Get_post_option::Get_post_option() : Option (std::string("GET,POST")) {}

void Get_post_option::doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) {

    filter (req, (drogon::FilterCallback &&) fcb,  (drogon::FilterChainCallback &&) fccb) ;
}
