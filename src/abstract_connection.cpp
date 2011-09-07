//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "abstract_connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace node {
namespace server {

abstract_connection::abstract_connection(boost::asio::io_service& io_service,
    connection_manager& manager, request_handler& handler)
    : socket_(io_service),
    connection_manager_(manager),
    request_handler_(handler)
{
}

boost::asio::ip::tcp::socket& abstract_connection::socket()
{
  return socket_;
}

} // namespace server
} // namespace node
