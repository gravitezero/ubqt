//
// abstract_reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "abstract_reply.hpp"
#include "reply_file.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace node {
namespace server {

class reply_file; // TODO Is it needed ?

abstract_reply* abstract_reply::create()
{
    return new reply_file(); // TODO change that and check the fucking template switch !!
    // TODO Check if this new will conclude to memory leak ?
    // -> use boost::shared_ptr !
}

abstract_reply::abstract_reply()
: still_data(true)
{
}

} // namespace server
} // namespace node
