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
#include "request.hpp"
#include "abstract_reply.hpp"

namespace node {
namespace server {

//struct reply;
//class reply;
struct request;

/// The common handler for all incoming requests.
class communication_handler
    : private boost::noncopyable
{
public:
    /// Construct with a directory containing files to be served.
    explicit communication_handler(const std::string& root_path);

    int handle_request(const request& req, reply_ptr rep);
    int handle_reply(const reply& rep, request_ptr req);

private:

    abstract_reply_ptr getTableHandle(const request& req);
    abstract_reply_ptr submitValueHandle(const request& req);
    abstract_reply_ptr ackValueHandle(const request& req);
    abstract_reply_ptr requestValueHandle(const request& req);
    abstract_reply_ptr refuseValueHandle(const request& req);
    abstract_reply_ptr registerListener(const request& req);
    // TODO Add here some others request handler like add a listener, remove a listener etc...

    /// Point to the request to send.
    //request& request_;
    
    /// Provide an access to the files to send.
    file_provider file_provider_;

};

} // namespace server
} // namespace node

#endif // COMMUNICATION_HANDLER_HPP

