/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>

namespace arolios {
using namespace drogon;
namespace ctlr {
class Nothing {
public:
     void options (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const ;
     
    void options_1 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1) const;
          
    void options_2 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2) const;

    void options_3 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3 ) const;

    void options_4 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4 ) const;

    void options_5 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5) const;

    void options_6 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6) const;

    void options_7 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7) const;

    void options_8 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8) const;
    
    void options_9 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8, std::string&& p_str9 ) const;
     
    void options_10 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8, std::string&& p_str9, std::string&& p_str10 ) const;

    void options_11 (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_str1, std::string&& p_str2, std::string&& p_str3, std::string&& p_str4, std::string&& p_str5, std::string&& p_str6, std::string&& p_str7, std::string&& p_str8, std::string&& p_str9, std::string&& p_str10, std::string&& p_str11 ) const;
     
     static void common_options (const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    
};
}
}

