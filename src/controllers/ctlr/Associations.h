/*
 *
 * Copyright (C) 2024 Philippe Coicadan. All rights reserved.
 * License: AGPL-3.0-or-later
 *
 */
#pragma once
#include <drogon/HttpController.h>
#include <ctlr/Classifiers.h>
#include <ctlr/Nothing.h>
#include <omm/Association.h>
#include <filter/RAC_util.h>

namespace arolios {


using namespace drogon;

namespace ctlr

{
class Associations : public drogon::HttpController<Associations> {
public:
  METHOD_LIST_BEGIN


  ADD_METHOD_TO(ctlr::Nothing::options_8,
                "/associations/{1}/instances?o={2}&l={3}&s={4}&d={5}&f={6}&p={7}&lang={8}",
                Options, "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Classifiers<omm::Association>::list_instances,
                "/associations/{1}/instances?o={2}&l={3}&s={4}&d={5}&f={6}&p={7}&lang={8}",
                drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  ADD_METHOD_TO(ctlr::Nothing::options_1, "/associations/{1}/instances", Options,
                "arolios::filter::Post_option");
  ADD_METHOD_TO(ctlr::Classifiers<omm::Association>::create_instance, "/associations/{1}/instances", drogon::Post,
                "arolios::filter::Login", arolios::filter::RAC_util::Producer());

  ADD_METHOD_TO(ctlr::Nothing::options_7,
                "/associations/{1}/properties?o={2}&l={3}&s={4}&d={5}&c={6}&lang={7}",
                Options, "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Classifiers<omm::Association>::list_properties,
                "/associations/{1}/properties?o={2}&l={3}&s={4}&d={5}&c={6}&lang={7}",
                drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  ADD_METHOD_TO(ctlr::Nothing::options_5,
                "/associations?o={1}&l={2}&s={3}&d={4}&lang={5}", Options,
                "arolios::filter::Get_option");
  ADD_METHOD_TO(ctlr::Classifiers<omm::Association>::list, "/associations?o={1}&l={2}&s={3}&d={4}&lang={5}",
                drogon::Get, "arolios::filter::Login", arolios::filter::RAC_util::Reader());

  METHOD_LIST_END

};
} // namespace ctlr
}

