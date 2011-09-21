//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"
#include <boost/bind.hpp>
#include <signal.h>

namespace node {
namespace server {

server::server(const std::string& address, const std::string& port, const std::string& root_path)
    : io_service_(),
      signals_(io_service_),
      acceptor_(io_service_),
      connection_manager_(),
      new_connection_(),
      communication_handler_(root_path)
{
    // Register to handle the signals that indicate when the server should exit.
    // It is safe to register for the same signal multiple times in a program,
    // provided all registration for the specified signal is made through Asio.
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
    #if defined(SIGQUIT)
        signals_.add(SIGQUIT);
    #endif // defined(SIGQUIT)
    signals_.async_wait(boost::bind(&server::handle_stop, this));

    // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query(address, port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    start_accept();
}

void server::run()
{
    // The io_service::run() call will block until all asynchronous operations
    // have finished. While the server is running, there is always at least one
    // asynchronous operation outstanding: the asynchronous accept call waiting
    // for new incoming connections.
    //io_service_.run();
    
    worker = boost::thread( boost::bind(&boost::asio::io_service::run, &io_service_));
}

void server::join()
{
    worker.join();
}

void server::start_accept()
{
    // TODO il faut un pattern pour fabriquer 2 types de connections : listening, et writing.
    new_connection_.reset(new connection(io_service_,
        connection_manager_, communication_handler_));
    acceptor_.async_accept(new_connection_->socket(),
        boost::bind(&server::handle_accept, this,
            boost::asio::placeholders::error));
}

void server::handle_accept(const boost::system::error_code& e)
{
    // Check whether the server was stopped by a signal before this completion
    // handler had a chance to run.
    if (!acceptor_.is_open())
    {
        return;
    }

    if (!e)
    {
        connection_manager_.start_read(new_connection_);
    }

    start_accept();
}

void server::handle_stop()
{
    // The server is stopped by cancelling all outstanding asynchronous
    // operations. Once all operations have finished the io_service::run() call
    // will exit.  
    acceptor_.close();
    connection_manager_.stop_all();
}

void server::add_connection(connection_ptr connection)
{
    // Here we want this connection start by sending something.
    // This new connection will herit from the legacy connection.
    // The legacy connection start by reading, this new connection will start by sending.
    connection_manager_.start_write(connection);
}

} // namespace server
} // namespace node
