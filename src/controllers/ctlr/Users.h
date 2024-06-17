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
#include <qry/Users_list.h>
#include <qry/User_read.h>
#include <mttr/User_create.h>
#include <mttr/User_update.h>
#include <mttr/User_delete.h>
#include <filter/RAC_util.h>

namespace arolios {


using namespace drogon;

namespace ctlr 
{
class Users:public drogon::HttpController<Users>
{
  public:
    METHOD_LIST_BEGIN

      ADD_METHOD_TO(ctlr::Nothing::options_5, "/users?o={1}&l={2}&s={3}&d={4}&lang={5}",Options, "arolios::filter::Get_option");
      ADD_METHOD_TO(ctlr::Base_resource::list<qry::Users_list>, "/users?o={1}&l={2}&s={3}&d={4}&lang={5}", drogon::Get, "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      
      ADD_METHOD_TO(ctlr::Nothing::options, "/users",Options, "arolios::filter::Post_option");
      ADD_METHOD_TO(ctlr::Base_resource::create<mttr::User_create>, "/users", drogon::Post , "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());

      ADD_METHOD_TO(ctlr::Nothing::options_3, "/users/{1}?c={2}&lang={3}", Options,  "arolios::filter::Get_option");
      ADD_METHOD_TO(ctlr::Base_resource::read<qry::User_read>,  "/users/{1}?c={2}&lang={3}", drogon::Get,  "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      
      ADD_METHOD_TO(ctlr::Nothing::options_1, "/users/{1}", Options,  "arolios::filter::Patch_delete_option");
      ADD_METHOD_TO(ctlr::Base_resource::update<mttr::User_update>,  "/users/{1}", drogon::Patch,  "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      ADD_METHOD_TO(ctlr::Base_resource::deletion<mttr::User_delete>, "/users/{1}", drogon::Delete , "arolios::filter::Login", "arolios::filter::RAC_default_app",  arolios::filter::RAC_util::Admin());
      

    METHOD_LIST_END
	
 
        void create ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback ) const;
        
        void list ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction ) const;
                
        void update ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_item_id ) const;
        
        void deletion ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_item_id ) const;
            
};
}
}

