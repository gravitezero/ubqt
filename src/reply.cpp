//
// reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "reply.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace node {
namespace server {

reply::reply(communication_handler& handler)
    : message(handler)
{
}

int reply::handle(request& req)
{
    communication_handler_.handle_reply(this, req);
}

int reply::parse(char* begin, char* end)
{
    reply_code_ = (ReplyCode)*begin;
    
    // TODO à finir
    
    return true;
}

std::vector<boost::asio::const_buffer> reply::to_buffers()
{
    // TODO a ameliore grandement, parce que là c'est vraiment la merde.
    // La merde ! vous dis-je.
    
    static char buffer[300];
    std::vector<boost::asio::const_buffer> buffers;

    buffers.push_back(boost::asio::buffer(value)); //TODO j'ai écrit value, mais je sais que c'est faux, il faut placer le code, puis value.
    still_data = false; // TODO still_data est un moyen vraiment tres mauvais de dire que la transaction est terminé, vraiment tres mauvais.

    return buffers;
}

} // namespace server
} // namespace node
