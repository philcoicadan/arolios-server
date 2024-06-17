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
#include <qry/App_users_list.h>
#include <mttr/App_user_create.h>
#include <mttr/App_user_delete.h>
#include <filter/RAC_util.h>

namespace arolios {


using namespace drogon;

namespace ctlr 
{
class App_users:public drogon::HttpController<App_users>
{
  public:
    METHOD_LIST_BEGIN
    
        ADD_METHOD_TO(ctlr::Nothing::options_5, "/appusers?o={1}&l={2}&s={3}&d={4}&lang={5}", Options,  "arolios::filter::Get_option");
        ADD_METHOD_TO(ctlr::Base_resource::list<qry::App_users_list>, "/appusers?o={1}&l={2}&s={3}&d={4}&lang={5}", drogon::Get , "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
        
        ADD_METHOD_TO(ctlr::Nothing::options, "/appusers",Options, "arolios::filter::Post_option");
        ADD_METHOD_TO(ctlr::Base_resource::create<mttr::App_user_create>, "/appusers", drogon::Post ,  "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
        
        ADD_METHOD_TO(ctlr::Nothing::options_1, "/appusers/{1}", Options,  "arolios::filter::Delete_option");
        ADD_METHOD_TO(ctlr::Base_resource::deletion<mttr::App_user_delete>, "/appusers/{1}", drogon::Delete, "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      
      
   
    METHOD_LIST_END
   
    
  
};
}
}

