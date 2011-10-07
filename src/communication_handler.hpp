//
// communication_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef COMMUNICATION_HANDLER_HPP
#define COMMUNICATION_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include "file_provider.hpp"
//#include "message.hpp"
//#include "request.hpp"
//#include "reply.hpp"

namespace node {
namespace server {

class message;
typedef boost::shared_ptr<message> message_ptr;
class request;
class reply;

/// The common handler for all incoming requests.
class communication_handler
    : private boost::noncopyable
{
public:
    /// Construct with a directory containing files to be served.
    explicit communication_handler(const std::string& root_path);

    int handle_request(request* const req, reply& rep);
    int handle_reply(reply* const rep, request& req);

private:

    int requestValueHandle(const request* const req, reply& rep);
    int sendValueHandle(const reply* const rep, request& req);
    
    
    
    /*message_ptr getTableHandle(const request& req);
    message_ptr submitValueHandle(const request& req);
    message_ptr ackValueHandle(const request& req);
    message_ptr requestValueHandle(const request& req);
    message_ptr refuseValueHandle(const request& req);
    message_ptr registerListener(const request& req);*/
    // TODO Add here some others request handler like add a listener, remove a listener etc...

    /// Point to the request to send.
    //request& request_;
    
    /// Provide an access to the files to send.
    file_provider file_provider_;

};

} // namespace server
} // namespace node

#endif // COMMUNICATION_HANDLER_HPP

