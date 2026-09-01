/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <drogon/drogon.h>
#include <ostream>
#include <svru/About.h>

int main(int argc, char *argv[]) {

  std::cout << arolios::svru::About::notice_text(); 


  if (argc > 1) {
    const std::string config_file(argv[1]);
    // Load config file
    drogon::app().loadConfigFile(config_file);
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return EXIT_SUCCESS;
  } else {
    std::cerr << "Argument missing, config file is expected" << std::endl;
    return EXIT_FAILURE;
  }

}
