/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>
#include <ctlr/Nothing.h>
#include <filter/RAC_util.h>

namespace arolios {

using namespace drogon;

namespace ctlr

{
class Enumerations : public drogon::HttpController<Enumerations> {
public:
  METHOD_LIST_BEGIN

  ADD_METHOD_TO(ctlr::Nothing::options_6,
                "/enumerations/{1}/values?o={2}&l={3}&s={4}&d={5}&lang={6}",
                Options, "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Enumerations::values,
                "/enumerations/{1}/values?o={2}&l={3}&s={4}&d={5}&lang={6}",
                drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  ADD_METHOD_TO(ctlr::Nothing::options_5,
                "/enumerations?o={1}&l={2}&s={3}&d={4}&lang={5}", Options,
                "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Enumerations::list, "/enumerations?o={1}&l={2}&s={3}&d={4}&lang={5}",
                drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  METHOD_LIST_END


  void list(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            std::string &&p_offset, std::string &&p_limit, std::string &&p_sort,
            std::string &&p_direction, std::string &&p_lang) const;
  void values(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&p_enum,
                       std::string &&p_offset, std::string &&p_limit,
                       std::string &&p_sort, std::string &&p_direction,
                       std::string &&p_lang) const;
};

} // namespace ctlr
}

