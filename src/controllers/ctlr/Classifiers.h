/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>
#include <filter/RAC_util.h>

namespace arolios {

using namespace drogon;

namespace ctlr

{
template <typename T> class Classifiers  {
public:
  
  

  void list_instances(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&p_elem,
                      std::string &&p_offset, std::string &&p_limit,
                      std::string &&p_sort, std::string &&p_direction,
                      std::string &&p_filters, std::string &&p_prop_list,
                      std::string &&p_lang) const;
  void create_instance(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&p_elem) const;
  void list(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            std::string &&p_offset, std::string &&p_limit, std::string &&p_sort,
            std::string &&p_direction, std::string &&p_lang) const;
  void list_properties(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&p_elem,
                       std::string &&p_offset, std::string &&p_limit,
                       std::string &&p_sort, std::string &&p_direction,
                       std::string &&p_context, std::string &&p_lang) const;
};

} // namespace ctlr
}

