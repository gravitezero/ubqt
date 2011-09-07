//
// abstract_connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ABSTRACT_CONNECTION_HPP
#define ABSTRACT_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "abstract_reply.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace node {
namespace server {

class connection_manager;

/// Represents a single connection from a client.
class abstract_connection
    : public boost::enable_shared_from_this<abstract_connection>,
      private boost::noncopyable
{
public:

    /// Get the socket associated with the connection.
    boost::asio::ip::tcp::socket& socket();

    /// Start the first asynchronous operation for the connection.
    virtual void start() = 0;    

    /// Stop all asynchronous operations associated with the connection.
    virtual void stop() = 0;

protected:

    /// Construct a connection with the given io_service.
    explicit abstract_connection(boost::asio::io_service& io_service,
        connection_manager& manager, request_handler& handler);
                
    /// Handle completion of a read operation.
    virtual void handle_read(const boost::system::error_code& e,
      std::size_t bytes_transferred) = 0;

    /// Handle completion of a write operation.
    virtual void handle_write(const boost::system::error_code& e) = 0;

    /// Socket for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// The manager for this connection.
    connection_manager& connection_manager_;

    /// The handler used to process the incoming request.
    request_handler& request_handler_;

    /// Buffer for incoming data.
    boost::array<char, 8192> buffer_;

    /// The incoming request.
    request request_;

    /// The parser for the incoming request.
    request_parser request_parser_;

    /// The reply to be sent back to the client.
    abstract_reply_ptr reply_;
};

typedef boost::shared_ptr<abstract_connection> connection_ptr;

} // namespace server
} // namespace node

#endif // ABSTRACT_CONNECTION_HPP

