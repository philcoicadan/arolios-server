/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Translations.h>
#include <drogon/HttpTypes.h>
#include <json/json.h>
#include <model/Model_tlt_loader.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <exception/Exceptions.h>





using namespace arolios;
using namespace arolios::ctlr;


void Translations::load(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const {

    

    MultiPartParser fileUpload;
    try {
        if ( fileUpload.parse ( req ) != 0 || fileUpload.getFiles().size() != 1 ) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody ( "Must only be one file" );
            resp->setStatusCode ( drogon::k400BadRequest );
            svru::Response::add_allow_headers (resp, req) ;
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

        model::Model_tlt_loader tlt_loader;
        tlt_loader.execute ( drogon::app().getUploadPath() + '/' + name );


        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody ("Translations loaded successfully");
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    }
    catch (const exception::Input_error &e) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(e.what());
        resp->setStatusCode(k400BadRequest);
        svru::Response::add_allow_headers(resp, req);

        callback(resp);
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

