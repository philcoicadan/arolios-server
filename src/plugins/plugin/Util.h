/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once

#include <string>


namespace arolios {


namespace plugin
{

class Util 
{
  public:
      
    static void info_begin (const std::string& p_pgn_name) ;

    static void info_end_ok ();

    static void info_end_ko (const std::string& p_message) ;
};

}
}
