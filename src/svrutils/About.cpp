/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <svru/About.h>



using namespace arolios;
using namespace arolios::svru;


const std::string & About::notice_text () {

    static const std::string text( std::string ("AROLIOS is a trademark registered in France.\n") +
      std::string ("AROLIOS Server is a web server implementing the AROLIOS API.\n" ) +
      std::string ("Copyright (C) 2024 Philippe Coicadan. All rights reserved.\n" ) +
      std::string ("License: AGPL-3.0-or-later\n"));

      return text;
  ;
    
}
