/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>
#include <ctlr/Nothing.h>
#include <omm/Association.h>
#include <omm/Enum_value.h>
#include <omm/Enumeration.h>
#include <filter/RAC_util.h>

namespace arolios {

using namespace drogon;

namespace omm {
  class Class;
  class Association;
  class Enumeration;
};


namespace ctlr 
{
class Domains:public drogon::HttpController<Domains>
{
  public:
    METHOD_LIST_BEGIN
   
    ADD_METHOD_TO(ctlr::Nothing::options_5, "/domains?o={1}&l={2}&s={3}&d={4}&lang={5}", Options, "arolios::filter::Get_option");
    ADD_METHOD_TO(ctlr::Domains::list, "/domains?o={1}&l={2}&s={3}&d={4}&lang={5}", drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());


    ADD_METHOD_TO(ctlr::Nothing::options_6,"/domains/{1}/classes?o={2}&l={3}&s={4}&d={5}&lang={6}",Options, "arolios::filter::Get_option");
    ADD_METHOD_TO(ctlr::Domains::list_classifiers<omm::Class>,"/domains/{1}/classes?o={2}&l={3}&s={4}&d={5}&lang={6}", drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());
    
    ADD_METHOD_TO(ctlr::Nothing::options_6, "/domains/{1}/associations?o={2}&l={3}&s={4}&d={5}&lang={6}",Options, "arolios::filter::Get_option");
    ADD_METHOD_TO(ctlr::Domains::list_classifiers<omm::Association>, "/domains/{1}/associations?o={2}&l={3}&s={4}&d={5}&lang={6}", drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());
    
    ADD_METHOD_TO(ctlr::Nothing::options_6, "/domains/{1}/enumerations?o={2}&l={3}&s={4}&d={5}&lang={6}",Options, "arolios::filter::Get_option");
    ADD_METHOD_TO(ctlr::Domains::list_classifiers<omm::Enumeration>, "/domains/{1}/enumerations?o={2}&l={3}&s={4}&d={5}&lang={6}", drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());
    

    METHOD_LIST_END

    
        void list ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction, std::string&& p_lang ) const;

        template <typename T> void list_classifiers ( const HttpRequestPtr& req,std::function<void ( const HttpResponsePtr & ) > &&callback, std::string&& p_pk_name, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction, std::string&& p_lang  ) const;

    
    
};
}
}

