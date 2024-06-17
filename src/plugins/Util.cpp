/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <plugin/Util.h>
#include <iostream>

using namespace arolios;
using namespace arolios::plugin;

      
void Util::info_begin (const std::string& p_pgn_name)
{
    std::cout << "INFO: plugin " << p_pgn_name << "...";
}

void Util::info_end_ok () 
{
    std::cout << "started." << std::endl;
}

void Util::info_end_ko (const std::string& p_message) 
{
    std::cout << "failed. " << p_message <<  std::endl;
}
