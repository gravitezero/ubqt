//
// request_get_table.hpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REQUEST_GET_TABLE_HPP
#define REQUEST_GET_TABLE_HPP

#include <boost/asio.hpp>

#include "abstract_request.hpp"

namespace node {
namespace server {

class request_request_value : public abstract_reply
{
public:
    request_request_value();
    
private:

};

} // namespace server
} // namespace node

#endif // REQUEST_GET_TABLE_HPP
