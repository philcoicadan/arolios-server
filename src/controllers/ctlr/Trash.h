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
class Trash:public drogon::HttpController<Trash>
{
  public:
    METHOD_LIST_BEGIN
 
      
    ADD_METHOD_TO(ctlr::Nothing::options_6, "/trash?o={1}&l={2}&s={3}&d={4}&f={5}&lang={6}",Options, "arolios::filter::Get_option");
    ADD_METHOD_TO(ctlr::Trash::list_instances, "/trash?o={1}&l={2}&s={3}&d={4}&f={5}&lang={6}", drogon::Get , "arolios::filter::Login", arolios::filter::RAC_util::Producer());
 
    ADD_METHOD_TO(ctlr::Nothing::options_1, "/trash/{1}", Options, "arolios::filter::Patch_delete_option");    
    ADD_METHOD_TO(ctlr::Trash::recover_instance, "/trash/{1}", drogon::Patch , "arolios::filter::Login", arolios::filter::RAC_util::Producer());
    ADD_METHOD_TO(ctlr::Trash::eliminate_instance, "/trash/{1}", drogon::Delete , "arolios::filter::Login", arolios::filter::RAC_util::Admin());
   
    ADD_METHOD_TO(ctlr::Nothing::options, "/trash",Options, "arolios::filter::Delete_option");
    ADD_METHOD_TO(ctlr::Trash::empty, "/trash", drogon::Delete, "arolios::filter::Login", arolios::filter::RAC_util::Admin());    
    
 
    METHOD_LIST_END
	

        void list_instances ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction, std::string&& p_filters, std::string&& p_lang ) const;

        void recover_instance ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_trash_id ) const;
        void eliminate_instance ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback,  std::string&& p_trash_id ) const;

        void empty ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback ) const;
  
  
};
}
}

