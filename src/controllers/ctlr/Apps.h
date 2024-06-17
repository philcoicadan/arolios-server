/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>
#include <ctlr/Nothing.h>
#include <ctlr/Base_resource.h>
#include <qry/App_read.h>
#include <qry/Apps_list.h>
#include <mttr/App_create.h>
#include <mttr/App_update.h>
#include <mttr/App_delete.h>
#include <filter/RAC_util.h>

namespace arolios {


using namespace drogon;

namespace ctlr 
{
class Apps:public drogon::HttpController<Apps>
{
  public:
    METHOD_LIST_BEGIN
    
      
      
      
      ADD_METHOD_TO(ctlr::Nothing::options_5, "/apps?o={1}&l={2}&s={3}&d={4}&lang={5}",Options, "arolios::filter::Get_option");
      ADD_METHOD_TO(ctlr::Base_resource::list<qry::Apps_list>, "/apps?o={1}&l={2}&s={3}&d={4}&lang={5}", drogon::Get, "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      
      ADD_METHOD_TO(ctlr::Nothing::options, "/apps",Options, "arolios::filter::Post_option");
      ADD_METHOD_TO(ctlr::Base_resource::create<mttr::App_create>, "/apps", drogon::Post , "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
   
      ADD_METHOD_TO(ctlr::Nothing::options_3, "/apps/{1}?c={2}&lang={3}", Options,  "arolios::filter::Get_option");
      ADD_METHOD_TO(ctlr::Base_resource::read<qry::App_read>,  "/apps/{1}?c={2}&lang={3}", drogon::Get,  "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());

      ADD_METHOD_TO(ctlr::Nothing::options_1, "/apps/{1}", Options,  "arolios::filter::Patch_delete_option");
      ADD_METHOD_TO(ctlr::Base_resource::update<mttr::App_update>,  "/apps/{1}", drogon::Patch,  "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      ADD_METHOD_TO(ctlr::Base_resource::deletion<mttr::App_delete>, "/apps/{1}", drogon::Delete , "arolios::filter::Login", "arolios::filter::RAC_default_app",  arolios::filter::RAC_util::Admin());
      

      ADD_METHOD_TO(ctlr::Nothing::options_1, "/apps/{1}/config",Options, "arolios::filter::Post_option");
      ADD_METHOD_TO(ctlr::Apps::load_config, "/apps/{1}/config", drogon::Post, "arolios::filter::Login", arolios::filter::RAC_util::Admin());
      



    METHOD_LIST_END

        void load_config(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_app_id) const;
    
};
}
}

