/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once

#include <string>

namespace arolios {


namespace filter {
class RAC_util {
public:


    static const std::string& Admin () ;

    static const std::string& Producer () ;

    static const std::string& Reader () ;
};
}
}

