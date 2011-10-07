//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONNECTION_CPP
#define CONNECTION_CPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "reply.hpp"
#include "request.hpp"
#include "connection_manager.hpp"
#include "communication_handler.hpp"

#include "connection_ptr.hpp"

namespace node {
namespace server {

/// Represents a single connection from a client.
template <class Incoming, class Outcoming>
class connection
    : public boost::enable_shared_from_this<connection<Incoming, Outcoming> >,
      private boost::noncopyable
{
//public:
    /// Construct a connection with the given io_service.
    /*explicit connection(boost::asio::io_service& io_service,
        connection_manager& manager, communication_handler& handler);

    /// Get the socket associated with the connection.
    boost::asio::ip::tcp::socket& socket();
    
    /// Get the outcoming message associated with the connection.
    Outcoming outcoming();

    /// Start the first asynchronous operation for the connection.
    void start_read();
    
    /// Start the first asynchronous operation for the connection.
    void start_write();

    /// Stop all asynchronous operations associated with the connection.
    void stop();*/

private:
    /// Handle completion of a read operation.
    //void handle_read(const boost::system::error_code& e, std::size_t bytes_transferred);

    /// Handle completion of a write operation.
    //void handle_write(const boost::system::error_code& e);

    /// Socket for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// The manager for this connection.
    connection_manager& connection_manager_;

    /// The handler used to process the incoming request.
    communication_handler& communication_handler_;

    /// Buffer for incoming data.
    boost::array<char, 8192> buffer_;

    /// The incoming message.
    Incoming incoming_;

    /// The outcoming message.
    Outcoming outcoming_;
    
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

    boost::asio::ip::tcp::socket& socket()
    {
      return socket_;
    }

    Outcoming& outcoming()
    {
        return outcoming_;
    }

    void start_read()
    {
        socket_.async_read_some(boost::asio::buffer(buffer_),
            boost::bind(&connection<Incoming, Outcoming>::handle_read, this->shared_from_this(),
                boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

    void start_write()
    {
        boost::asio::async_write(socket_, outcoming_.to_buffers(),
            boost::bind(&connection<Incoming, Outcoming>::handle_write, this->shared_from_this(),
                boost::asio::placeholders::error));
    }

    void stop()
    {
        socket_.close();
    }

    void handle_read(const boost::system::error_code& e,
        std::size_t bytes_transferred)
    {
        if (!e)
        {
            boost::tribool result = incoming_.parse(
                buffer_.data(), buffer_.data() + bytes_transferred);

            if (result)
            {
                if ( true == incoming_.handle(outcoming_) )
                {// TODO changer pour quelque chose de plus propre
                    boost::asio::async_write(socket_, outcoming_.to_buffers(),
                        boost::bind(&connection<Incoming, Outcoming>::handle_write, this->shared_from_this(),
                            boost::asio::placeholders::error));
                }
                else
                {
                    // Initiate graceful connection closure.
                    boost::system::error_code ignored_ec;
                    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
                    
                        if (e != boost::asio::error::operation_aborted)
                        {
                            connection_manager_.stop(this->shared_from_this());
                        }
                }
            }

            // TODO prendre en charge les erreurs
            /*else if (!result)
            {
                reply_ = reply::stock_reply(reply::bad_request);
                    boost::asio::async_write(socket_, outcoming_.to_buffers(),
                        boost::bind(&handle_write, this->shared_from_this(),
                            boost::asio::placeholders::error));
            }
            else
            {
                socket_.async_read_some(boost::asio::buffer(buffer_),
                    boost::bind(&handle_read, this->shared_from_this(),
                        boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
            }*/
        }
        else if (e != boost::asio::error::operation_aborted)
        {
            connection_manager_.stop(this->shared_from_this());
        }
    }

    void handle_write(const boost::system::error_code& e)
    {
        if (outcoming_.still_data)
        {
            boost::asio::async_write(socket_, outcoming_.to_buffers(),
                boost::bind(&connection<Incoming, Outcoming>::handle_write, this->shared_from_this(),
                    boost::asio::placeholders::error));
                    
            return;
        }

        if (!e)
        {
            // Initiate graceful connection closure.
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }

        if (e != boost::asio::error::operation_aborted)
        {
            connection_manager_.stop(this->shared_from_this());
        }
    }
    
};

} // namespace server
} // namespace node

#endif // CONNECTION_CPP

