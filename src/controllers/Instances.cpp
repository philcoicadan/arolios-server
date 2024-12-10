/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <ctlr/Instances.h>
#include <mttr/Classifier_instance_factory.h>
#include <mttr/Classifier_instance_delete.h>
#include <mttr/Classifier_instance_update.h>
#include <mttr/Data_import.h>
#include <common/App_info.h>
#include <common/Singleton.h>
#include <common/Object_model_info.h>
#include <qry/Association_instance_read.h>
#include <qry/Class_instance_read.h>
#include <qry/Instance_assoc_instances_list.h>
#include <tqry/Exporter.h>
#include <qry/Instance_filter.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <util/String.h>
#include <svru/Request.h>
#include <svru/Response.h>
#include <qry/Return_code.h>
#include <drogon/HttpTypes.h>




using namespace arolios;
using namespace arolios::ctlr;


void Instances::update(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string &&p_inst_id) const {


	  try {

        auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();
       
        const auto [csf_id, row_id] =
        qry::Util::split_instance_id(p_inst_id);           

        // lookup classifier

        auto csf =
        om_ptr->find_domain_element_by_id<omm::Classifier>(std::to_string(csf_id));
  

        auto resp = HttpResponse::newHttpResponse();
                

        auto json_ptr = req->jsonObject() ;

        if (json_ptr == nullptr) {
          throw exception::Input_error("Data missing");
        }

        if (csf) {
          const int upd_count = json_ptr->get("upd_count", 0).asInt();

          auto iu = mttr::Classifier_instance_factory::instance().make_update(
              csf, *json_ptr, p_inst_id, upd_count);
          if (iu) {
            iu->execute();

            if (iu->return_code() == qry::Return_code::OK) {
              resp->setStatusCode(drogon::k200OK);
              resp->setContentTypeCode(CT_TEXT_HTML);
              resp->setBody("Instance updated ");
            } else {
              resp->setStatusCode(drogon::k400BadRequest);
              resp->setContentTypeCode(CT_TEXT_HTML);
              resp->setBody("Instance updating failed ");
            }
          } else {
            resp->setStatusCode(k500InternalServerError);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody("Classifier without relational object ");
          }
        } else {
          resp->setStatusCode(k400BadRequest);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Classifier not found ");
        }

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
    catch ( const std::exception&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
         
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    } 
}




void Instances::deletion(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&p_inst_id) const {

	
	  try {

        auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();
        const auto [csf_id, row_id] =
        qry::Util::split_instance_id(p_inst_id);

        // lookup classifier

        auto csf =
        om_ptr->find_domain_element_by_id<omm::Classifier>(std::to_string(csf_id));
  

        auto resp = HttpResponse::newHttpResponse();
                

        auto json_ptr = req->jsonObject() ;

        if (csf) {
          const int upd_count = (json_ptr == nullptr) ? 0 : json_ptr->get("upd_count", 0).asInt();

          auto id = mttr::Classifier_instance_factory::instance().make_delete(
              csf, p_inst_id, upd_count);
          if (id) {
            id->execute();

            if (id->return_code() == qry::Return_code::OK) {
              resp->setStatusCode(drogon::k200OK);
              resp->setContentTypeCode(CT_TEXT_HTML);
              resp->setBody("Instance deleted ");
            } else {
              resp->setStatusCode(drogon::k400BadRequest);
              resp->setContentTypeCode(CT_TEXT_HTML);
              resp->setBody("Instance deletion failed ");
            }
          } else {
            resp->setStatusCode(k500InternalServerError);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody("Classifier without relational object ");
          }
        } else {
          resp->setStatusCode(k400BadRequest);
          resp->setContentTypeCode(CT_TEXT_HTML);
          resp->setBody("Classifier not found ");
        }
        
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
    catch ( const std::exception&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
         
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    } 
}


  void Instances::read(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            std::string &&p_inst_id, std::string &&p_usage,
            std::string &&p_lang) const {


	  try {
	    auto app_ptr = common::Singleton<common::App_info>::instance().object();

        auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();
       
        auto lang = app_ptr->get_language_by_code(util::String::standardize (p_lang));
        
        auto && usage = ( p_usage.length() == 0 ) ? "ro" : util::String::standardize ( p_usage );
        if ( usage != "ro" && usage != "rfu" ) {
            std::cout << "WARNING: read mode " << usage << "is unknown, default mode (read only) is applied" << std::endl;;
            usage = "ro";
        }
        
  

        qry::Util::Read_mode read_mode = qry::Util::convert_read_mode ( usage );

      const auto [csf_id, row_id] =
        qry::Util::split_instance_id(p_inst_id);
        
        // lookup class at first

        auto cls =
        om_ptr->find_domain_element_by_id<omm::Class>(std::to_string(csf_id));
 
       
      
        auto resp = HttpResponse::newHttpResponse();

        if (cls) {
          std::shared_ptr<omm::Table> elem_lo = cls->table();

          if (elem_lo) {

            // add filter to select only active (non-deleted) instance
            const std::shared_ptr<const qry::Instance_filter> td_filter =
                std::make_shared<qry::Instance_filter>("trashed_date", "=",
                                                       "'epoch'");
            const std::vector<std::shared_ptr<const qry::Instance_filter>>
                filters = {td_filter};

            qry::Class_instance_read ir(cls, p_inst_id, read_mode, filters,
                                        lang);
            ir.execute();

            if (ir.return_code() == qry::Return_code::OK) {
              const Json::Value &json = ir.return_json();

              resp = HttpResponse::newHttpJsonResponse(json);

            } else {
              resp->setStatusCode(drogon::k400BadRequest);
              resp->setContentTypeCode(CT_TEXT_HTML);
              resp->setBody("Instance reading failed ");
            }
          } else {
            resp->setStatusCode(k500InternalServerError);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody("Class without relational object ");
          }

        } else {
          const auto assoc =
              om_ptr->find_domain_element_by_id<omm::Association>(
                  std::to_string(csf_id));
          if (assoc) {

            // add filter to select only active (non-deleted) instance
            const std::shared_ptr<const qry::Instance_filter> td_filter =
                std::make_shared<qry::Instance_filter>("trashed_date", "=",
                                                       "'epoch'");
            const std::vector<std::shared_ptr<const qry::Instance_filter>>
                filters = {td_filter};

            qry::Association_instance_read ir(assoc, p_inst_id, read_mode,
                                              filters, lang);
            ir.execute();

            if (ir.return_code() == qry::Return_code::OK) {
              const Json::Value &json = ir.return_json();

              resp = HttpResponse::newHttpJsonResponse(json);

            } else {
              resp->setStatusCode(k400BadRequest);
              resp->setContentTypeCode(CT_TEXT_HTML);
              resp->setBody("Instance reading failed ");
            }

          } else {
            resp->setStatusCode(k400BadRequest);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody("Classifier not found ");
          }
        }
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
    catch ( const std::exception&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
         
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    } 
}
            

void
  Instances::list_assoc_instances(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&p_inst_id, std::string &&p_prop_id,
                       std::string &&p_offset, std::string &&p_limit,
                       std::string &&p_sort, std::string &&p_direction,
                       std::string &&p_filters, std::string &&p_prop_list,
                       std::string &&p_lang) const {
    
    

    try {
        auto app_ptr = common::Singleton<common::App_info>::instance().object();

        auto om_ptr = common::Singleton<common::Object_model_info>::instance().object();

        auto lang = app_ptr->get_language_by_code(p_lang);

        auto list_params =
        svru::Request::check_list_params(p_sort, p_direction, p_limit, p_offset);

       

        auto && prop_list = p_prop_list;
        if ( prop_list.empty()) {
            prop_list = "LIST"; // no export option 
        } else {
             std::transform ( prop_list.begin(), prop_list.end(), prop_list.begin(),
                             [] ( unsigned char c ) -> unsigned char {return std::toupper ( c ); } );
        }


        if ( prop_list != "ALL" && prop_list != "LIST" ) {
            std::cout << ": properties parameter " << prop_list << "is unknown, default mode (all) is applied" ;
            prop_list = "ALL";
        }

      
        auto filters = qry::Instance_filter::make_fts_filters(p_filters);
        
        //add filter to select only active (non-deleted) instances
        const std::shared_ptr<const qry::Instance_filter> td_filter = std::make_shared<const qry::Instance_filter>("trashed_date", "=", "'epoch'") ;
        filters.push_back(td_filter);


        auto resp = HttpResponse::newHttpResponse();
        
       
        // lookup class
        // if inheritance, the class can have sub-classes
        const auto [csf_id, row_id] =
        qry::Util::split_instance_id(p_inst_id);
            auto cls =
        om_ptr->find_domain_element_by_id<omm::Class>(std::to_string(csf_id));

        
        if ( cls ) {

              const auto prop = svru::Request::is_id (p_prop_id) ?
                om_ptr->find_property_by_id (p_prop_id) :
                cls->find_property_member_end( p_prop_id) ;

                if (prop && (cls->is_kind_of (prop->classifier()))) {
                    
                    qry::Instance_assoc_instances_list il ( cls, p_inst_id, prop, p_prop_id, prop->association(), list_params.offset_, list_params.limit_,
                      list_params.sort_, list_params.direction_, filters, prop_list , lang);
             
                    il.execute (); 
                    
                    if ( il.return_code () == qry::Return_code::OK ) {
                        const Json::Value & json = il.return_json();

                        resp = HttpResponse::newHttpJsonResponse ( json );


                    } else {
                        resp->setStatusCode ( drogon::k400BadRequest );
                        resp->setContentTypeCode ( CT_TEXT_HTML );
                        resp->setBody ( "Instance associations list failed " );
                    }
                } else {
                    resp->setStatusCode ( k400BadRequest );
                    resp->setContentTypeCode ( CT_TEXT_HTML );
                    resp->setBody ( "Property is not a member end of an association of the class" );
                }

        } else {
            resp->setStatusCode ( k400BadRequest );
            resp->setContentTypeCode ( CT_TEXT_HTML );
            resp->setBody ( "Class not found " );
        }

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
    catch ( const std::exception&  e ) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody ( e.what() );
         
        resp->setStatusCode ( k500InternalServerError );
        svru::Response::add_allow_headers (resp, req) ;

        callback ( resp );
        return;
    } 
}
                       

void Instances::import(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const {

  


  MultiPartParser fileUpload;
 try {
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Must only be one file");
        resp->setStatusCode(drogon::k400BadRequest);
        svru::Response::add_allow_headers(resp, req);

        callback(resp);

        return;
    }

 
    auto &file = fileUpload.getFiles()[0];
    auto md5 = file.getMd5();
    auto len = file.fileLength();
    auto ext = file.getFileExtension();
    auto name = file.getFileName();
    auto type = file.getFileType();

    file.save();
    std::cout << "INFO: The uploaded file has been saved to the ./uploads "
                 "directory" << std::endl;

    mttr::Data_import importer(drogon::app().getUploadPath() + '/' + name);
    importer.execute();

    auto resp = HttpResponse::newHttpResponse();
    resp->setContentTypeCode(CT_TEXT_HTML);

    if (importer.return_code() == qry::Return_code::OK) {
      resp->setStatusCode(drogon::k200OK);
      resp->setBody("File imported ");
    } else {
      resp->setStatusCode(drogon::k400BadRequest);
      resp->setBody("File imported with errors");
    }

    svru::Response::add_allow_headers(resp, req);

    callback(resp);
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
  catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());

    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}


  void Instances::query_from_files(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback) const {


  

  MultiPartParser fileUpload;


  try {
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() > 2) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("One or two files are expected");
        resp->setStatusCode(drogon::k400BadRequest);
        svru::Response::add_allow_headers(resp, req);
        callback(resp);
        return;
    }

    std::string names[2];
    const int nb_files = fileUpload.getFiles().size();
    for (int i = 0; i < nb_files; ++i) {
      auto &file = fileUpload.getFiles()[i];
      auto md5 = file.getMd5();
      auto len = file.fileLength();
      auto ext = file.getFileExtension();
      names[i] = file.getFileName();
      auto type = file.getFileType();



      file.save();
      std::cout << "INFO: The uploaded file have been saved to the ./uploads "
                  "directory" << std::endl;
    }

    auto resp = HttpResponse::newHttpResponse();
    if (nb_files > 0) {
      tqry::Exporter q(drogon::app().getUploadPath() + '/' + names[0]);

      if (nb_files > 1) {
        q.param_file(drogon::app().getUploadPath() + '/' + names[1]);
      }
      q.execute();

     

      if (q.return_code() == qry::Return_code::OK) {
        const Json::Value &json = q.return_json();

        resp = HttpResponse::newHttpJsonResponse(json);


      } else {
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody("Query failed ");
      }
    } else {
      resp->setStatusCode(k400BadRequest);
      resp->setContentTypeCode(CT_TEXT_HTML);
      resp->setBody("Query failed ");
    }

    svru::Response::add_allow_headers(resp, req);

    callback(resp);
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
  catch (const std::exception &e) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(e.what());
     
    resp->setStatusCode(k500InternalServerError);
    svru::Response::add_allow_headers(resp, req);

    callback(resp);
    return;
  }
}



