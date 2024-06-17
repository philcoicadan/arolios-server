/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <filter/RAC_util.h>
#include <common/User_role.h>




using namespace arolios;
using namespace arolios::filter;



const std::string& RAC_util::Admin () {
        static std::string role =  "arolios::filter::RAC_user_role<" + std::to_string(static_cast<int>(common::User_role::admin)) +">";
        return role;
    }

const std::string& RAC_util::Author () {
        static std::string role =  "arolios::filter::RAC_user_role<" + std::to_string(static_cast<int>(common::User_role::author)) +">";
        return role;
    }

const std::string& RAC_util::Reader () {
        static std::string role =  "arolios::filter::RAC_user_role<" + std::to_string(static_cast<int>(common::User_role::reader)) +">";
        return role;
    }
