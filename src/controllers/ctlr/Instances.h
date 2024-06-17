/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <ctlr/Nothing.h>
#include <drogon/HttpController.h>
#include <filter/RAC_util.h>

namespace arolios {

using namespace drogon;

namespace ctlr

{
class Instances : public drogon::HttpController<Instances> {
public:
  METHOD_LIST_BEGIN

  ADD_METHOD_TO(ctlr::Nothing::options_3, "/instances/{1}?c={2}&lang={3}", Options,
             "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Instances::read, "/instances/{1}?c={2}&lang={3}", drogon::Get,
             "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  ADD_METHOD_TO(ctlr::Nothing::options_1, "/instances/{1}", Options,
             "arolios::filter::Patch_delete_option");
  ADD_METHOD_TO(ctlr::Instances::update, "/instances/{1}", drogon::Patch,
             "arolios::filter::Login", arolios::filter::RAC_util::Author());
  ADD_METHOD_TO(ctlr::Instances::deletion, "/instances/{1}", drogon::Delete,
             "arolios::filter::Login", arolios::filter::RAC_util::Author());

  ADD_METHOD_TO(ctlr::Nothing::options_9,
             "/instances/{1}/association_ends/{2}?o={3}&l={4}&s={5}&d={6}&f={7}&p={8}&lang={9}",
             Options, "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Instances::list_assoc_instances,
             "/instances/{1}/association_ends/{2}?o={3}&l={4}&s={5}&d={6}&f={7}&p={8}&lang={9}",
             drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  ADD_METHOD_TO(ctlr::Nothing::options, "/instances", Options, "arolios::filter::Put_post_option");
  ADD_METHOD_TO(ctlr::Instances::import, "/instances", drogon::Put, "arolios::filter::Login",
             arolios::filter::RAC_util::Author());
  ADD_METHOD_TO(ctlr::Instances::query_from_files, "/instances", drogon::Post,
             "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  METHOD_LIST_END

  void update(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string &&p_inst_id) const;
  void deletion(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&p_inst_id) const;
  void read(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            std::string &&p_inst_id, std::string &&p_usage,
            std::string &&p_lang) const;

  void
  list_assoc_instances(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&p_inst_id, std::string &&p_prop_id,
                       std::string &&p_offset, std::string &&p_limit,
                       std::string &&p_sort, std::string &&p_direction,
                       std::string &&p_filters, std::string &&p_prop_list,
                       std::string &&p_lang) const;

  void import(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const;

  void query_from_files(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback) const;
};

} // namespace ctlr
}

