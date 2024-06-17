/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <string>
#include <drogon/HttpAppFramework.h>

namespace arolios {

namespace svru {

class Response {
public:
  
  static void add_allow_headers (const drogon::HttpResponsePtr& p_resp, const drogon::HttpRequestPtr& p_req);

  static void add_allow_methods (const drogon::HttpResponsePtr& p_resp, const drogon::HttpRequestPtr& p_req, const std::string& p_requested_method) ;

};

} }

