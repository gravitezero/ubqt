//
// abstract_reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <string>
#include <boost/shared_ptr.hpp>

#include "abstract_reply.hpp"
#include "reply_file.hpp"

namespace node {
namespace server {

boost::shared_ptr<abstract_reply> abstract_reply::create(std::string content)
{
    return boost::shared_ptr<abstract_reply>(new reply_file(content));
}

abstract_reply::abstract_reply()
: still_data(true)
{
}

} // namespace server
} // namespace node
