//
// reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "reply.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace node {
namespace server {

std::vector<boost::asio::const_buffer> reply::to_buffers()
{
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(content));
    return buffers;
}

} // namespace server
} // namespace node
