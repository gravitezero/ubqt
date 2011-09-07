//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp> 

#include "abstract_connection.hpp"
#include "input_connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace node {
namespace server {

/// The top-level class of the node server.
class server
    : private boost::noncopyable
{
public:
    /// Construct the server to listen on the specified TCP address and port,
    /// and serve up files from the given directory.
    explicit server(const std::string& address, const std::string& port,
        const std::string& root_path);

    /// Run the server's io_service loop.
    void run();
    
    void join();

private:
    /// Initiate an asynchronous accept operation.
    void start_accept();

    /// Handle completion of an asynchronous accept operation.
    void handle_accept(const boost::system::error_code& e);

    /// Handle a request to stop the server.
    void handle_stop();

    /// The io_service used to perform asynchronous operations.
    boost::asio::io_service io_service_;

    /// The signal_set is used to register for process termination notifications
    boost::asio::signal_set signals_;

    /// Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor acceptor_;

    /// The connection manager which owns all live connections.
    connection_manager connection_manager_;

    /// The next connection to be accepted.
    connection_ptr new_connection_;

    /// The handler for all incoming requests.
    request_handler request_handler_;
    
    void add_connection(connection_ptr connection);
    
    boost::thread worker;
};

} // namespace server
} // namespace node

#endif // SERVER_HPP
