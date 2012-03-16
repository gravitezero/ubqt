//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
namespace node {
namespace server {
    
    connection::connection(boost::asio::io_service& io_service,
    connection_manager& manager, communication_handler& handler_)
    : socket_(io_service),
    connection_manager_(manager),
    communication_handler_(handler_),
    incoming_(communication_handler_),
    outcoming_(communication_handler_)
    {
    }

    boost::asio::ip::tcp::socket& connection::socket()
    {
      return socket_;
    }

    Outcoming& connection::outcoming()
    {
        return outcoming_;
    }

    void connection::start_read()
    {
        // TODO maybe getting the buffer from the message could avoid copying data to the message
        socket_.async_read_some(boost::asio::buffer(buffer_),
            boost::bind(&connection<Incoming, Outcoming>::handle_read, this->shared_from_this(),
                boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

    void connection::start_write()
    {
        boost::asio::async_write(socket_, outcoming_.to_buffers(),
            boost::bind(&connection<Incoming, Outcoming>::handle_write, this->shared_from_this(),
                boost::asio::placeholders::error));
    }

    void connection::stop()
    {
        socket_.close();
    }


    void connection::handle_read(const boost::system::error_code& e,
        std::size_t bytes_transferred)
    {
    
        std::cout << "byte transferred : " << bytes_transferred << std::endl;
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
            std::cout << "got an error " << e << std::endl;
        }
    }

    void connection::handle_write(const boost::system::error_code& e)
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
