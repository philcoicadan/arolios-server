/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Models.h>
#include <drogon/HttpTypes.h>
#include <json/json.h>
#include <model/Model_loader.h>
#include <svru/Request.h>
#include <svru/Response.h>




using namespace arolios;
using namespace arolios::ctlr;


void Models::load(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const {

    

    MultiPartParser fileUpload;

    if ( fileUpload.parse ( req ) != 0 || fileUpload.getFiles().size() != 1 ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( "Only one file is expected" );
        resp->setStatusCode ( drogon::k400BadRequest );
        svru::Response::add_allow_headers (resp, req) ;
        callback ( resp );
        return;
    }

    try {
        auto &file = fileUpload.getFiles() [0];
        auto md5 = file.getMd5();
        auto len = file.fileLength();
        auto ext = file.getFileExtension ();
        auto name = file.getFileName();
        auto type = file.getFileType ();

        

        file.save();
        std::cout << "INFO: The uploaded file has been saved to the ./uploads "
                 "directory";

        model::Model_loader mdl_loader;
        mdl_loader.execute ( drogon::app().getUploadPath() + '/' + name );


        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody ("Model loaded successfully");
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

