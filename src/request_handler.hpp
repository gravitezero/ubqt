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

namespace node {
namespace server {

struct reply;
struct request;

/// The common handler for all incoming requests.
class request_handler
    : private boost::noncopyable
{
public:
    /// Construct with a directory containing files to be served.
    explicit request_handler(const std::string& root_path);

    /// Handle a request and produce a reply.
    void handle_request(const request& req, reply& rep);

private:

    void getTableHandle(const request& req, reply& rep);
    void submitValueHandle(const request& req, reply& rep);
    void ackValueHandle(const request& req, reply& rep);
    void requestValueHandle(const request& req, reply& rep);
    void refuseValueHandle(const request& req, reply& rep);
    
    // TODO Add here some others request handler like add a listener, remove a listener etc...

    file_provider file_provider_;

};

} // namespace server
} // namespace node

#endif // REQUEST_HANDLER_HPP

