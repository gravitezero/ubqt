//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>
#include "protocole.hpp"

namespace node {
namespace server {

/// A request received from a client.
struct request
{
    CommandCode command;
    std::string value;
};

} // namespace server
} // namespace node

#endif // REQUEST_HPP
