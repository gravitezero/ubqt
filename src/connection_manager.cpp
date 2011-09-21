//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection_manager.hpp"
#include <algorithm>
#include <boost/bind.hpp>

namespace node {
namespace server {

void connection_manager::start_read(connection_ptr c)
{
    // TODO Add a mutex here if needed.
    connections_.insert(c);
    c->start_read();
}

void connection_manager::start_write(connection_ptr c)
{
    // TODO Add a mutex here if needed.
    connections_.insert(c);
    c->start_write();
}

void connection_manager::stop(connection_ptr c)
{
    connections_.erase(c);
    c->stop();
}

void connection_manager::stop_all()
{
    std::for_each(connections_.begin(), connections_.end(),
        boost::bind(&abstract_connection::stop, _1));
    connections_.clear();
}

} // namespace server
} // namespace node
