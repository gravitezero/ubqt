//
// reply_simple.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REPLY_SIMPLE_HPP
#define REPLY_SIMPLE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

#include "message.hpp"

namespace node {
namespace server {

enum ReplyCode {
    SEND_TABLE,
    SEND_VALUE,
    REFUSE_SENDING,
    ACCEPT_RECEIVING,
    REFUSE_RECEIVING
};

class reply : public message
{
public:
    reply();

    std::vector<boost::asio::const_buffer> to_buffers();
    void set_content(std::string content);
    
private:
    ReplyCode reply_code_;
    std::string value;
        
        
};

} // namespace server
} // namespace node

#endif // REPLY_FILE_HPP
