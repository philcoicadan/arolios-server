/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <plugin/App_server.h>
#include <plugin/Object_model.h>
#include <plugin/Util.h>
#include <qry/App_retriever.h>
#include <qry/Model_retriever.h>
#include <qry/Init_retriever.h>
#include <util/String.h>
#include <exception/Exceptions.h>
#include <omm/Classifier.h>
#include <omm/Class.h>
#include <omm/Association.h>
#include <omm/Enumeration.h>
#include <omm/Data_type.h>
#include <omm/Language.h>
#include <omm/Enum_value.h>
#include <omm/Package.h>
#include <appcfg/App.h>
#include <appcfg/App_domain.h>
#include <appcfg/Base_classifier_config.h>
#include <appcfg/Factory.h>
#include <omm/Model_factory.h>
#include <common/Singleton.h>







using namespace arolios;
using namespace arolios::plugin;

App_server::App_server() {


}

App_server::~App_server () {
    
}


void App_server::initAndStart(const Json::Value &p_config) {

    Util::info_begin("App_server");

    // set common object
    common::Singleton<App_info>::instance().object(this);

    
    //init root of app domains
    init_root ();
      
	// get values in the config file
	if (!p_config) {
        Util::info_end_ko("No information in the config file." );
		return;
	}
	
    
    qry::Init_retriever init_rtv;
    
    default_app_id_ = init_rtv.retrieve_param ("default_app");
    const auto default_language_id =  init_rtv.retrieve_param ("default_language");
    
    if ( default_app_id_.empty() || default_language_id.empty() ){
        // database not initialized
        Util::info_end_ko("Database not initialized." );
        return;
    }
      

    
    auto  mdl_info = common::Singleton<common::Object_model_info>::instance().object();
         
    qry::App_retriever app_rtv ;   
    
    default_app_ = app_rtv.retrieve_app(default_app_id_);

	auto app_name = p_config.get("appname",default_app_->name()).asString();

    
    // for cross origin request - default: not authorized
    auto authorized_origins = p_config.get("ip_domain_origins", "").asString();
    auto origin_vec = util::String::split(authorized_origins, ' ');
    for (auto origin : origin_vec) {
        
        ip_domain_origins_.insert(origin);
    }
    
    const auto default_language = app_rtv.retrieve_language(default_language_id);
    
    auto language_code = p_config.get("language", default_language->code()).asString();

	
    
    std::shared_ptr<omm::Package> root_pk =  mdl_info->root_domain() ;
    
    if (root_pk) {
        // database initialized
        
        
        if ( language_code != default_language->code() ) {
            language_code = util::String::standardize ( language_code );
        }

        if ( app_name != default_app_->name() ) {
            app_name = util::String::standardize ( app_name );
            app_ = app_rtv.retrieve_app_by_name ( app_name );
        } else {
            app_ = default_app_;
        }


        
        app_rtv.retrieve_languages ();
        
        set_default_language ( language_code, default_language->code());

        
        
        if (app_) {
            // app registered
            

            
            qry::Model_retriever mdl_rtv ;
            const auto std_dom =  mdl_info->standard_domain();
            insert<omm::Package>( std_dom );
            mdl_rtv.retrieve_standard_types ();
            mdl_rtv.retrieve_properties ( std_dom) ;
            mdl_rtv.retrieve_logical_fields ( std_dom ); 
	  

            // retrieve packages from the app config
            for ( auto app_domain : app_->app_domains() )
            {
           
                const auto & pk = (app_domain.second)->domain();

                if ( pk ) {
                    //insert domain in the app list
                    insert<omm::Package> ( pk );

                    //retrieve its classifiers
                    mdl_rtv.retrieve_classifiers ( pk );

                    // retrieve enumeration values
                    mdl_rtv.retrieve_enumeration_values ( pk );

                    // retrieve_properties
                    mdl_rtv.retrieve_properties ( pk );

                     // retrieve_logical_fields
                    // must be done after properties because the order of fields is different
                    mdl_rtv.retrieve_logical_fields ( pk ); 
                    
                    // retrieve_field_constraints
                    mdl_rtv.retrieve_field_constraints ( pk );
                    
                    mdl_rtv.retrieve_identifiers (pk);
                    
                    //compute all properties and all specializations for all classifiers ( class + association)
                    for (auto cls: pk->classes()) {
                        cls.second->make_all_elements_as_property(true);
                        cls.second->make_more_specific_ids(true);
                    }

                    for (auto assoc: pk->associations()) {
                        assoc.second->make_all_elements_as_property(true);
                        assoc.second->make_more_specific_ids(true);
                    }

                    
                    //initialize domain config for classes and associations
                    create_domain_config(pk);
                    
                    // retrieve config for classifiers and collections of properties
                    app_rtv.retrieve_app_config (app_, pk);
                    
                    // prepare queries for list and read functions
                    app_domain.second->create_select_templates();
                    
 
                    //TODO in the future: constraints
                    
                } else {
                    std::string msg ( "domain not found" );
                    exception::Failure e ( msg );
                    throw e;
                }

            }
            
            // retrieve translations for all app domains + std_dom
        
            app_rtv.retrieve_translations (std_dom) ;
            
            for ( auto app_domain : app_->app_domains() )
            {

                const auto & pk = (app_domain.second)->domain();

                if ( pk ) {
                  app_rtv.retrieve_translations (pk) ;  
                }
            }
        
        } else {
            std::string msg ( "application " + app_name + " not found" );
            exception::Not_found e ( msg );
            throw e;
        }
        
        Util::info_end_ok ();


    }
    else {
              // database not initialized, nothing to do
            Util::info_end_ko("Database not initialized.");

    }
}

void App_server::shutdown() {
    
}
    

const std::unordered_set<std::string>& App_server::authorized_origins () const {
    return ip_domain_origins_;
}

