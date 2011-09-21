//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>

namespace node {
namespace server {

enum RequestCode {
    GET_TABLE,
    SUBMIT_VALUE,
    REQUEST_VALUE
};

/// A request received from a client.
class request : public message
{
public:
    request();
    
    std::vector<boost::asio::const_buffer> to_buffers();

protected:
    RequestCode request_code_;
    std::string value;
};

} // namespace server
} // namespace node

#endif // REQUEST_HPP
