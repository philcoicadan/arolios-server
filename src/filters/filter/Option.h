/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpFilter.h>
#include <string>

namespace arolios {


namespace filter {
class Option  {
public:

    void filter(const drogon::HttpRequestPtr &req,
                          drogon::FilterCallback &&fcb,
                          drogon::FilterChainCallback &&fccb) ;
 
protected:

        /**
     * Constructor
     */
    Option( const std::string& p_requested_method) ;
   

private:
    
    std::string requested_method_ ;

};


}
}

