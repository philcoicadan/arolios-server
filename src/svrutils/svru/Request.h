/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <string>

namespace arolios {

namespace svru {

class Request {
public:
  struct List_params {
    std::string sort_;
    std::string direction_;
    std::string limit_;
    std::string offset_;
  };

  static List_params check_list_params(const std::string &p_sort,
                                       const std::string &p_dir,
                                       const std::string &p_limit,
                                       const std::string &p_offset,
                                       bool p_sort_with_path = true);

  static std::string check_prop_list_mode(const std::string p_prop_list_mode);

  static std::string check_element_id(const std::string &p_elem_id);

  static bool is_id (const std::string& p_elem_id);

};

} }

