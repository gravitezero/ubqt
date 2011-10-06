//
// connection_manager.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <set>
#include <boost/noncopyable.hpp>

#include "connection.cpp"

namespace node {
namespace server {

/// Manages open connections so that they may be cleanly stopped when the server
/// needs to shut down.
class connection_manager
    : private boost::noncopyable
{
public:
    /// Add the specified listening connection to the manager and start it.
    void start(listening_connection_ptr c);
    
    /// Add the specified client connection to the manager and start it.
    void start(client_connection_ptr c);    

    /// Stop the specified listening connection.
    void stop(listening_connection_ptr c);
    
    /// Stop the specified client connection.
    void stop(client_connection_ptr c);

    /// Stop all connections.
    void stop_all();

private:
    /// The managed connections.
    /// Listening connections
    std::set<listening_connection_ptr> listening_connections_;
    /// Client connections
    std::set<client_connection_ptr> client_connections_;
};

} // namespace server
} // namespace node

#endif // CONNECTION_MANAGER_HPP
