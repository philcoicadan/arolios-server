/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <omm/Language.h>
#include <omm/Package.h>
#include <string>
#include <drogon/plugins/Plugin.h>
#include <json/json.h>
#include <common/App_info.h>

namespace arolios {



namespace appcfg {
    class App;
    class App_domain;
    class Base_classifier_config;
}

namespace plugin
{

class App_server : public drogon::Plugin<App_server>, public common::App_info
{
  public:
      
    App_server() ;
    
    virtual ~App_server () ;
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    virtual void initAndStart(const Json::Value &config) override;

    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    virtual void shutdown() override;
       
 	
    const std::unordered_set<std::string>&  authorized_origins () const;
    
    
protected:

    
private:
    
    std::unordered_set<std::string> ip_domain_origins_; //need for cross origin requests
  

};

}
}

