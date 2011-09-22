//
// request.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace node {
namespace server {

request::request(communication_handler& handler)
    : message(communication_handler& handler)
{
}

int request::handle(message_ptr msg)
{
    handler.handle_request(msg, this);
}

int request::parse(char* begin, char* end)
{
    request_code_ = (RequestCode)*buffer;
    
    If (request_code_ == GET_VALUE)
    {
        value.assign(buffer, 1, end - begin); // TODO à changer, pas propre.
    }
    
    return true;
}

std::vector<boost::asio::const_buffer> request::to_buffers()
{
    // TODO a ameliore grandement, parce que là c'est vraiment la merde.
    // La merde ! vous dis-je.
    
    static char buffer[300];
    std::vector<boost::asio::const_buffer> buffers;

    buffers.push_back(boost::asio::buffer(request_code_))
    buffers.push_back(boost::asio::buffer(value));
    still_data = false; // TODO still_data est un moyen vraiment tres mauvais de dire que la transaction est terminé.

    return buffers;
}

} // namespace server
} // namespace node
