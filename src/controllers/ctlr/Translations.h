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
class Translations:public drogon::HttpController<Translations>
{
  public:
    METHOD_LIST_BEGIN

      
      ADD_METHOD_TO(ctlr::Nothing::options, "/translations", Options, "arolios::filter::Post_option");
      ADD_METHOD_TO(ctlr::Translations::load, "/translations", drogon::Post, "arolios::filter::Login", "arolios::filter::RAC_default_app", arolios::filter::RAC_util::Admin());
      
      

    METHOD_LIST_END


	void load(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const;
    
    

   
    
  
};
}
}

