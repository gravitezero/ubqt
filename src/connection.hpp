//
// connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

//#include "reply.hpp"
//#include "request.hpp"
#include "message.hpp"
#include "connection_manager.hpp"
#include "communication_handler.hpp"

#include "connection.hpp"

namespace node {
namespace server {

/// Represents a single connection from a client.
class connection
    : public boost::enable_shared_from_this<connection>,
      private boost::noncopyable
{
public:
    
    connection(boost::asio::io_service& io_service,
    connection_manager& manager, communication_handler& handler_)
    : socket_(io_service),
    connection_manager_(manager),
    communication_handler_(handler_),
    incoming_(communication_handler_),
    outcoming_(communication_handler_)
    {
    }

    boost::asio::ip::tcp::socket& socket();

    message& outcoming();

    void start_read();

    void start_write();

    void stop();

private:
    /// Handle completion of a read operation.
    void handle_read(const boost::system::error_code& e, std::size_t bytes_transferred);

    /// Handle completion of a write operation.
    void handle_write(const boost::system::error_code& e);

    /// Socket for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// The manager for this connection.
    connection_manager& connection_manager_;

    /// The handler used to process the incoming request.
    communication_handler& communication_handler_;

    /// Buffer for incoming data.
    boost::array<char, 8192> buffer_;

    /// The incoming message.
    message incoming_;

    /// The outcoming message.
    message outcoming_;    
};

} // namespace server
} // namespace node

#endif // CONNECTION_HPP

