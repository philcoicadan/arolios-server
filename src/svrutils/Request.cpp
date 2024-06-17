/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#include <svru/Request.h>
#include <svru/Response.h>
#include <util/String.h>
#include <cctype>
#include <drogon/HttpAppFramework.h>
#include <plugin/App_server.h>
#include <common/App_info.h>
#include <common/Singleton.h>


using namespace arolios;
using namespace arolios::svru;

Request::List_params Request::check_list_params(const std::string &p_sort,
                                    const std::string &p_direction,
                                    const std::string &p_limit,
                                    const std::string &p_offset,
                                    bool p_sort_with_path) {
  Request::List_params result;
  result.sort_ = p_sort;
  if (!result.sort_.empty()) {
    std::transform(
        result.sort_.begin(), result.sort_.end(), result.sort_.begin(),
        [](unsigned char c) -> unsigned char { return std::tolower(c); });
    if (result.sort_ != "id" ) { // csf_id not in API
      // check the sort criterion, can be a property path

      if (p_sort_with_path) {

        util::String::standardize(util::String::split(p_sort, '.'));
      } else {

        result.sort_ = util::String::standardize(result.sort_);
      }
    }
  }
 

  result.direction_ = p_direction;
  if (result.direction_.empty()) {
    result.direction_ = "ASC";
  } else {
    std::transform(
        result.direction_.begin(), result.direction_.end(),
        result.direction_.begin(),
        [](unsigned char c) -> unsigned char { return std::toupper(c); });
  }

  if (result.direction_ != "ASC" && result.direction_ != "DESC") {
    std::cout << "WARNING: direction " << result.direction_
              << "is unknown, default mode (asc) is applied" << std::endl;;
    result.direction_ = "ASC";
  }

  result.offset_ = p_offset;
  if (!result.offset_.empty()) {
    try {

      long num = std::stol(result.offset_);
    } catch (std::invalid_argument &e) {
      throw e;

    } catch (std::out_of_range &e) {
      throw e;
    }
  }

  result.limit_ = p_limit;
  if (!result.limit_.empty()) {
    try {

      long num = std::stol(result.limit_);
    } catch (const std::invalid_argument &e) {
      throw e;

    } catch (const std::out_of_range &e) {
      throw e;
    }
  }

  return result;
}

std::string Request::check_prop_list_mode(const std::string p_prop_list) {

  auto prop_list = p_prop_list;
  if (prop_list.empty()) {
    prop_list = "ALL";
  } else {
    std::transform(
        prop_list.begin(), prop_list.end(), prop_list.begin(),
        [](unsigned char c) -> unsigned char { return std::toupper(c); });
  }

  if (prop_list != "ALL" && prop_list != "LIST") {
   std::cout << "WARNING: properties parameter " << prop_list
              << "is unknown, default mode (all) is applied" << std::endl;
    prop_list = "ALL";
  }
  return prop_list;
}



std::string Request::check_element_id (const std::string& p_elem_id)
{
  if (is_id(p_elem_id)) {   
         try {

            unsigned long  elem_id = std::stoul ( p_elem_id ) ;
        } catch ( const std::invalid_argument& e ) {
            throw std::exception (e);
            
        } catch ( const std::out_of_range& e ) {
            throw std::exception (e);

        }

        return p_elem_id;
  }
  else {
    return util::String::standardize(p_elem_id);
  }
}

bool Request::is_id(const std::string &p_elem_id) {

  if (!p_elem_id.empty()) {
    if (std::isdigit(static_cast<unsigned char>( p_elem_id[0])) != 0) {
      return true;
    }
  }
  return false;
}
