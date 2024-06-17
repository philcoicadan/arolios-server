/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/Patch_option.h>

using namespace arolios;
using namespace arolios::filter;
Patch_option::Patch_option() : Option (std::string("PATCH")) {}
    
void Patch_option::doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) {

    filter (req, (drogon::FilterCallback &&) fcb,  (drogon::FilterChainCallback &&) fccb) ;
}
