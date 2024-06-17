/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/Get_patch_delete_option.h>

using namespace arolios;
using namespace arolios::filter;
Get_patch_delete_option::Get_patch_delete_option() : Option (std::string("GET,PATCH,DELETE")) {}
    
void Get_patch_delete_option::doFilter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) {

    filter (req, (drogon::FilterCallback &&) fcb,  (drogon::FilterChainCallback &&) fccb) ;
}
