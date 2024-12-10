/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <drogon/HttpTypes.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <drogon/HttpAppFramework.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <model/App_config_loader.h>
#include <ctlr/Apps.h>
#include "Base_resource.tpp"
#include <exception/Exceptions.h>








using namespace arolios;
using namespace arolios::ctlr ;

template void Base_resource::list<qry::Apps_list>(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_offset, std::string&& p_limit, std::string&& p_sort, std::string&& p_direction,  std::string&& p_lang  ) const ;

template void Base_resource::create<mttr::App_create>(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const;

template  void Base_resource::read<qry::App_read>(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_elem_id, std::string&& p_usage,  std::string&& p_lang ) const ;

 
template void Base_resource::update<mttr::App_update>(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&p_item_id) const;

template void Base_resource::deletion<mttr::App_delete>(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&p_item_id) const;


 

void Apps::load_config(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string&& p_app_id) const {
     
    

    MultiPartParser fileUpload;
    try {
        if ( fileUpload.parse ( req ) != 0 || fileUpload.getFiles().size() != 1 ) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody ( "Must only be one file" );
            resp->setStatusCode ( drogon::k400BadRequest );
            callback ( resp );
            return;
        }


        auto &file = fileUpload.getFiles() [0];
        auto md5 = file.getMd5();
        auto len = file.fileLength();
        auto ext = file.getFileExtension ();
        auto name = file.getFileName();
        auto type = file.getFileType ();

        

        file.save();
        std::cout << "INFO: The uploaded file has been saved to the ./uploads "
                 "directory" << std::endl;
        
 
        // the app name is the app identifier
        const std::string app_name = util::String::standardize(p_app_id);

        model::App_config_loader app_loader;
        app_loader.execute ( app_name, drogon::app().getUploadPath() + '/' + name );


        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody ("App config loaded successfully");
        //resp->setBody ("The server has calculated the file's MD5 hash to be " + md5 );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    }
    catch ( const exception::Input_error&  e  ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what());
        resp->setStatusCode ( k400BadRequest );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    } 
    catch ( const std::exception&  e  ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what());
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    }

}
