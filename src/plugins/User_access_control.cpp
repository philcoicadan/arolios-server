/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <plugin/User_access_control.h>
#include <plugin/Util.h>
#include <common/Db_client.h>
#include <util/String.h>
#include <common/User.h>
#include <common/Singleton.h>
#include <common/App_info.h>
#include <appcfg/App.h>
#include <qry/Init_retriever.h>
#include <util/String.h>
#include <exception/Exceptions.h>
#include <common/Singleton.h>





using namespace arolios;
using namespace arolios::plugin ;

User_access_control::User_access_control() {

}

User_access_control::~User_access_control() {

}

void User_access_control::initAndStart(const Json::Value &config) {


    Util::info_begin("User_access_control");

    // set object
    common::Singleton<UAC_info>::instance().object(this);

    
    // retrieve super_user
   
    auto clientPtr = common::Singleton<common::Db_client>::instance().object();
    
    qry::Init_retriever init_rtv;
    
    const std::string super_user_id = init_rtv.retrieve_param ("super_user");

    if (!super_user_id.empty()) { // the database is initialized
    
      const std::string stmt = "SELECT * FROM am_user WHERE id=$1";

      auto f = clientPtr->execSqlAsyncFuture(
          stmt, util::String::stoui(super_user_id));

      try {
        auto result = f.get();

        if (result.size() > 0) {
          auto row = result[0];

          common::User_role ur = role_cast(row["u_role"].as<std::string>());

          const std::string identifier = row["u_identifier"].as<std::string>();
          super_user_ = std::make_shared<common::User>();
          super_user_->identifier(identifier);

          unsigned int id = row["id"].as<unsigned int>();
          super_user_->persistent_attributes(std::to_string(id), "am_user");
          super_user_->app_role(ur);
        } else {
          std::string error_msg = "Super user not found";
           
          throw exception::Not_found(error_msg);
        }
      } catch (const exception::Db_exception &e) {
        std::cerr << "error: " << e.base().what() << std::endl;

        throw e;
      }

      Util::info_end_ok();
      return;
    }
    Util::info_end_ko("Database not initialized.");
}


void User_access_control::shutdown() {
   
    
}
