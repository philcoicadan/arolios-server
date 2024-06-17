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
#include <qry/App_domains_list.h>
#include <mttr/App_domain_create.h>
#include <mttr/App_domain_delete.h>
#include <filter/RAC_util.h>

namespace arolios {


using namespace drogon;

namespace ctlr 
{
class App_domains:public drogon::HttpController<App_domains>
{
  public:
    METHOD_LIST_BEGIN
    
        ADD_METHOD_TO(ctlr::Nothing::options_5, "/appdomains?o={1}&l={2}&s={3}&d={4}&lang={5}", Options,  "arolios::filter::Get_option");
        ADD_METHOD_TO(ctlr::Base_resource::list<qry::App_domains_list>, "/appdomains?o={1}&l={2}&s={3}&d={4}&lang={5}", drogon::Get , "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
        
        ADD_METHOD_TO(ctlr::Nothing::options, "/appdomains",Options, "arolios::filter::Post_option");
        ADD_METHOD_TO(ctlr::Base_resource::create<mttr::App_domain_create>, "/appdomains", drogon::Post ,  "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
        
        ADD_METHOD_TO(ctlr::Nothing::options_1, "/appdomains/{1}", Options,  "arolios::filter::Delete_option");
        ADD_METHOD_TO(ctlr::Base_resource::deletion<mttr::App_domain_delete>, "/appdomains/{1}", drogon::Delete, "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      
      
   
    METHOD_LIST_END
    
  
};
}
}

