//
// request_parser.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_parser.hpp"
#include "request.hpp"
#include "protocole.hpp"

namespace node {
namespace server {

request_parser::request_parser()
{

}

boost::tuple<boost::tribool, char*> request_parser::parse(request& req,
char* begin, char* end)
{
    req.command = (CommandCode)*begin;
    return boost::make_tuple(true, begin);
}

} // namespace server
} // namespace node
