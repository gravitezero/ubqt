//
// message.cpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "message.hpp"

namespace node {
namespace server {

message::message(communication_handler& handler)
    : still_data(true),
      communication_handler_(handler)
{
}

} // namespace server
} // namespace node
