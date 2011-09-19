//
// abstract_reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ABSTRACT_REPLY_HPP
#define ABSTRACT_REPLY_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

namespace node {
namespace server {

enum ReplyCode {
    SEND_TABLE,
    SEND_VALUE,
    REFUSE_SENDING,
    ACCEPT_RECEIVING,
    REFUSE_RECEIVING
};

class abstract_reply;
typedef boost::shared_ptr<abstract_reply> abstract_reply_ptr;

class abstract_reply
{
public:
    virtual std::vector<boost::asio::const_buffer> to_buffers() = 0;
    virtual void set_content(std::string content) = 0; //TODO remplacer std::string par un pointeur vers l'information
    static abstract_reply_ptr create(std::string content);
    
    bool still_data;

protected:

    abstract_reply();
    
    ReplyCode reply_;

};

} // namespace server
} // namespace node

#endif // ABSTRACT_REPLY_HPP
