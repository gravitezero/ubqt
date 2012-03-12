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
#include <boost/shared_array.hpp>

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
    new_connection_.reset(new listening_connection(io_service_, connection_manager_, communication_handler_));
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
        connection_manager_.start(new_connection_);
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

void server::add_connection(std::string host, std::string port, RequestCode reqCode)
{
    // Here we want this connection start by sending something.
    // This new connection will herit from the legacy connection.
    // The legacy connection start by reading, this new connection will start by sending.
    
        
    /// Make connection
    client_connection_ptr connection_(new client_connection(io_service_, connection_manager_, communication_handler_));
    
    /// Fill message
    //request* req = new request(communication_handler_);
    //request req = connection_->outcoming(); // TODO comment récupérer la référence de la requete pour la remplir ?
    //shared_array(boost::array<char, 1>) buffer_( new boost::array<char, 1>); //TODO doit être alloué dynamiquement, pour sortir de ce scope.
    // Peut être demander à request d'allouer lui-même ses buffer.
    
    int size_ = 30;
    char * buffer_ = new char[size_];
    //buffer_[0] = (char) reqCode;
    strcpy(buffer_, "the string I want to send");
    connection_->outcoming().parse(buffer_, (char*)(buffer_ + size_));
    
    /// Fill socket
    boost::system::error_code error = boost::asio::error::host_not_found;
    
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query(host, port);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    
    while (error && endpoint_iterator != end)
    {
      connection_->socket().close();
      connection_->socket().connect(*endpoint_iterator++, error);
    }
    if (error)
      throw boost::system::system_error(error);

    /// Start connection);
    connection_manager_.start(connection_);
}

} // namespace server
} // namespace node
