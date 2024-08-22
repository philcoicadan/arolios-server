/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Users.h>
#include "Base_resource.tpp"





using namespace arolios;
using namespace arolios::ctlr ;

template void Base_resource::list<qry::Users_list>(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction,  std::string&& p_lang  ) const ;

template void Base_resource::create<mttr::User_create>(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const;
 
template  void Base_resource::read<qry::User_read>(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_elem_id, std::string&& p_usage,  std::string&& p_lang ) const ;

template void Base_resource::update<mttr::User_update>(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&p_item_id) const;

template void Base_resource::deletion<mttr::User_delete>(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&p_item_id) const;
