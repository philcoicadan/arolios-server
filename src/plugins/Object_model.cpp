/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <plugin/Object_model.h>
#include <plugin/Util.h>
#include <omm/Model_factory.h>
#include <qry/Model_retriever.h>
#include <qry/Init_retriever.h>
#include <util/String.h>
#include <exception/Exceptions.h>
#include <drogon/HttpAppFramework.h>


using namespace drogon;
using namespace arolios;
using namespace arolios::plugin;

Object_model::Object_model () {
    root_pk_ = nullptr;
    std_pk_ = nullptr;
}

Object_model::~Object_model () { 
    
}

void Object_model::initAndStart ( const Json::Value &p_config ) {
    // Initialize and start the plugin

    Util::info_begin("Object_model");


    //set this as common object
    common::Singleton<common::Object_model_info>::instance().object(this);


    // set Db client as common object
    auto clientPtr = drogon::app().getDbClient();
    common::Singleton<common::Db_client>::instance().object(clientPtr);

    qry::Init_retriever init_rtv ;

    const auto root_domain_id = init_rtv.retrieve_param ( "root_domain" );
    const auto std_domain_id =  init_rtv.retrieve_param ( "standard_domain" );

    if ( !root_domain_id.empty() && !std_domain_id.empty() ) {



        qry::Model_retriever retrieve_v ;


        // check initialization
        retrieve_v.retrieve_init ( root_domain_id, std_domain_id );


        if ( ( root_pk_ ) && ( std_pk_ ) ) {

            retrieve_v.retrieve_user_domains ();

            Util::info_end_ok();
            return;

        }
    }
    Util::info_end_ko("Database not initialized.");


}

void Object_model::shutdown() 
{
    /// Shutdown the plugin
}

