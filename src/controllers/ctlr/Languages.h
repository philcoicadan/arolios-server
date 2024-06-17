/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <ctlr/Nothing.h>
#include <drogon/HttpController.h>
#include <drogon/HttpTypes.h>
#include <filter/RAC_util.h>

namespace arolios {

using namespace drogon;

namespace ctlr {
class Languages : public drogon::HttpController<Languages> {
public:
  METHOD_LIST_BEGIN

  ADD_METHOD_TO(ctlr::Nothing::options_1,
                "/languages?f={1}", Options,
                "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Languages::list,
                "/languages?f={1}", drogon::Get,
                "arolios::filter::Login", 
                arolios::filter::RAC_util::Reader());


  METHOD_LIST_END

  void list(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            std::string &&p_filters) const;

};
} // namespace ctlr
}

