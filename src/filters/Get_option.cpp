/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/Get_option.h>

using namespace arolios;
using namespace arolios::filter;

Get_option::Get_option() : Option (std::string("GET")) {}

void Get_option::doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) {

    filter (req, (drogon::FilterCallback &&) fcb,  (drogon::FilterChainCallback &&) fccb) ;
}
