//
// input_connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa dash lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef INPUT_CONNECTION_HPP
#define INPUT_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "abstract_connection.hpp"
#include "abstract_reply.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace node {
namespace server {

class connection_manager;

/// Represents a single connection from a client.
class input_connection
    : public abstract_connection
{
public:
    /// Construct a connection with the given io_service.
    explicit input_connection(boost::asio::io_service& io_service,
        connection_manager& manager, request_handler& handler);

    /// Start the first asynchronous operation for the connection.
    void start();    

    /// Stop all asynchronous operations associated with the connection.
    void stop();

//protected:
    /// Handle completion of a read operation.
    void handle_read(const boost::system::error_code& e,
      std::size_t bytes_transferred);

    /// Handle completion of a write operation.
    void handle_write(const boost::system::error_code& e);
};

} // namespace server
} // namespace node

#endif // INPUT_CONNECTION_HPP

