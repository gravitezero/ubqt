//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <boost/bind.hpp>

#include "connection.cpp"
#include "connection_manager.hpp"

namespace node {
namespace server {

void connection_manager::start(listening_connection_ptr c)
{
    // TODO Add a mutex here if needed.
    listening_connections_.insert(c);
    c->start_read();
}

void connection_manager::start(client_connection_ptr c)
{
    // TODO Add a mutex here if needed.
    client_connections_.insert(c);
    c->start_write();
}

void connection_manager::stop(listening_connection_ptr c)
{
    listening_connections_.erase(c);
    c->stop();
}

void connection_manager::stop(client_connection_ptr c)
{
    client_connections_.erase(c);
    c->stop();
}

void connection_manager::stop_all()
{
    std::for_each(listening_connections_.begin(), listening_connections_.end(),
        boost::bind(&listening_connection::stop, _1));
    listening_connections_.clear();
    
    std::for_each(client_connections_.begin(), client_connections_.end(),
        boost::bind(&client_connection::stop, _1));
    client_connections_.clear();
}

} // namespace server
} // namespace node
