/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/plugins/Plugin.h>
#include <json/json.h>
#include <omm/Package.h>
#include <omm/Classifier.h>
#include <omm/Data_type.h>
#include <omm/Property.h>
#include <omm/Enum_value.h>
#include <qry/Native_type.h>
#include <common/Singleton.h>
#include <common/Object_model_info.h>

namespace arolios {




namespace plugin
{

class Object_model : public drogon::Plugin<Object_model>, public common::Object_model_info
{
  public:
    
          
    Object_model() ;
    
    virtual ~Object_model ();
    
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    virtual void initAndStart(const Json::Value &config) override;

    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    virtual void shutdown() override;
    
   

protected:


private:
    
    
   

};

}

}

