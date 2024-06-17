/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/App_domains.h>
#include "Base_resource.tpp"






using namespace arolios;
using namespace arolios::ctlr ;

template void Base_resource::list<qry::App_domains_list>(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction,  std::string&& p_lang  ) const ;

  template void Base_resource::create<mttr::App_domain_create>(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const;
 
   template void Base_resource::deletion<mttr::App_domain_delete>(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&p_item_id) const;