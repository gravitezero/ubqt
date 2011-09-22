//
// message.hpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "communication_handler.hpp"

namespace node {
namespace server {

class message
    : public boost::enable_shared_from_this<message>,
      private boost::noncopyable
{
public:
    virtual int handle(message_ptr msg) = 0;  
    virtual int parse(buffer_ptr buffer) = 0;  
    virtual std::vector<boost::asio::const_buffer> to_buffers() = 0;
    
    bool still_data;
    
    friend class communication_handler;    

protected:

    message(communication_handler& handler);
    
    communication_handler& communication_handler_;

};

typedef boost::shared_ptr<message> message_ptr;

} // namespace server
} // namespace node

#endif // MESSAGE_HPP
