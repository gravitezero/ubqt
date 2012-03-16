//
// message.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>

#include <boost/asio.hpp>

typedef std::vector<void*> ptr_vector;

namespace node {
namespace server {

class message {

    public:
        message(unsigned int op_code, ptr_vector arguments);
        
        boost::asio::const_buffer to_buffer();
    
    protected:
        unsigned int op_code_;
        ptr_vector arguments_;
};

} // namespace server
} // namespace node

#endif // MESSAGE_HPP
