/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>

namespace arolios {



using namespace drogon;

namespace ctlr {
class Base_resource {
  // the class is not generic but the methods are generic because the parameter is specific for each method
public:
  template < typename TC> void create(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const;

  template < typename TR> void read(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string &&p_item_id, std::string &&p_usage, std::string &&p_lang) const;  
  
  template < typename TU> void update(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string &&p_item_id) const;

  template < typename TD> void deletion(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&p_item_id) const;

    template < typename TL> void list(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            std::string &&p_offset, std::string &&p_limit, std::string &&p_sort,
            std::string &&p_direction, std::string &&p_lang) const;
};
} // namespace ctlr
}

