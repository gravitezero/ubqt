//
// data_manager.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp> 
#include <boost/shared_ptr.hpp>

#include "connection.cpp"
#include "connection_manager.hpp"
#include "communication_handler.hpp"

namespace node {
namespace server {

/// data_manager
class data_manager
    : private boost::noncopyable
{
    public
        int get_data( int id, std::string& data);
        
        int append_data( int id, std::string data );
        
    private
        server server_;
        
        /// for debugging purpose, instead of a database, we use a single string to hold information.
        std::string data_;
};

} // namespace server
} // namespace node

#endif // DATA_MANAGER_HPP
