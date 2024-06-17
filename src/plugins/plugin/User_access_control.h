/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/plugins/Plugin.h>
#include <common/User_role.h>
#include <common/UAC_info.h>

namespace arolios {

namespace util {
    class User;
}

namespace plugin {
    
class User_access_control : public drogon::Plugin<User_access_control> , public common::UAC_info {
public:
    
    

    /**
     * Constructor
     */
    User_access_control();
    
    /**
     * Destructor
     */
    virtual ~User_access_control();
    
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

