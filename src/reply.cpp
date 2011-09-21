//
// reply_simple.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "reply_simple.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace node {
namespace server {

reply_simple::reply_simple(std::string content)
    : abstract_reply(),
      content(content)
{
}

void reply_simple::set_content(std::string content)
{
    content.append(content);
}

std::vector<boost::asio::const_buffer> reply_simple::to_buffers()
{
    // TODO a ameliore grandement, parce que là c'est vraiment la merde.
    // La merde ! vous dis-je.
    
    static char buffer[300];
    std::vector<boost::asio::const_buffer> buffers;

    buffers.push_back(boost::asio::buffer(content));
    still_data = false; // TODO still_data est un moyen vraiment tres mauvais de dire que la transaction est terminé, vraiment tres mauvais.

    return buffers;
}

} // namespace server
} // namespace node
