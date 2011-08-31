//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

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
class request_handler
    : private boost::noncopyable
{
public:
    /// Construct with a directory containing files to be served.
    explicit request_handler(const std::string& root_path);

    abstract_reply_ptr handle_request(const request& req);

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

#endif // REQUEST_HANDLER_HPP

