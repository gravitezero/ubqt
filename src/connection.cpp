//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace node {
namespace server {

connection::connection(boost::asio::io_service& io_service,
    connection_manager& manager, request_handler& handler)
    : socket_(io_service),
    connection_manager_(manager),
    communication_handler_(handler),
    incoming(communication_handler_),
    outcoming(communication_handler_)
{
}

boost::asio::ip::tcp::socket& connection::socket()
{
  return socket_;
}

abstract_message_ptr outcoming()
{
    return outcoming_;
}

void connection::start_read()
{
    socket_.async_read_some(boost::asio::buffer(buffer_),
        boost::bind(&connection::handle_read, shared_from_this(),
            boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void connection::start_write()
{
    boost::asio::async_write(socket_, outcoming_->to_buffers(),
        boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
}

void connection::stop()
{
    socket_.close();
}

void connection::handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
    if (!e)
    {
        boost::tribool result = incoming_->parse(
            buffer_.data(), buffer_.data() + bytes_transferred);

        if (result)
        {
            if ( true == incoming_->handle(outcoming_) )
            {// TODO changer pour quelque chose de plus propre
                boost::asio::async_write(socket_, outcoming_->to_buffers(),
                    boost::bind(&connection::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));
            }
            else
            {
                // Initiate graceful connection closure.
                boost::system::error_code ignored_ec;
                socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
                
                    if (e != boost::asio::error::operation_aborted)
                    {
                        connection_manager_.stop(shared_from_this());
                    }
            }
        }

        // TODO prendre en charge les erreurs
        /*else if (!result)
        {
            reply_ = reply::stock_reply(reply::bad_request);
                boost::asio::async_write(socket_, reply_.to_buffers(),
                    boost::bind(&connection::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));
        }
        else
        {
            socket_.async_read_some(boost::asio::buffer(buffer_),
                boost::bind(&connection::handle_read, shared_from_this(),
                    boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }*/
    }
    else if (e != boost::asio::error::operation_aborted)
    {
        connection_manager_.stop(shared_from_this());
    }
}

void connection::handle_write(const boost::system::error_code& e)
{
    if (reply_->still_data)
    {
        boost::asio::async_write(socket_, reply_->to_buffers(),
            boost::bind(&connection::handle_write, shared_from_this(),
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
        connection_manager_.stop(shared_from_this());
    }
}

} // namespace server
} // namespace node
