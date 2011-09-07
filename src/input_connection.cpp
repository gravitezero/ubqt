//
// input_connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa dash lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "input_connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace node {
namespace server {

input_connection::input_connection(boost::asio::io_service& io_service,
    connection_manager& manager, request_handler& handler)
    : abstract_connection(io_service, manager, handler)
{
}

void input_connection::start()
{
    socket_.async_read_some(boost::asio::buffer(buffer_),
        boost::bind(&input_connection::handle_read, boost::enable_shared_from_this<input_connection>::shared_from_this(),
            boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void input_connection::stop()
{
    socket_.close();
}

void input_connection::handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
    if (!e)
    {
        boost::tribool result;
        boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
            request_, buffer_.data(), buffer_.data() + bytes_transferred);

        if (result)
        {
            reply_ = request_handler_.handle_request(request_);
            boost::asio::async_write(socket_, reply_->to_buffers(),
                boost::bind(&input_connection::handle_write, shared_from_this(),
                    boost::asio::placeholders::error));
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
        connection_manager_.stop(boost::enable_shared_from_this<input_connection>::shared_from_this());
    }
}

void input_connection::handle_write(const boost::system::error_code& e)
{
    if (reply_->still_data)
    {
        //request_handler_.handle_request(request_, reply_);
        
        boost::asio::async_write(socket_, reply_->to_buffers(),
            boost::bind(&input_connection::handle_write, boost::enable_shared_from_this<input_connection>::shared_from_this(),
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
        connection_manager_.stop(boost::enable_shared_from_this<input_connection>::shared_from_this());
    }
}

} // namespace server
} // namespace node