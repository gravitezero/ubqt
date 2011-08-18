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

reply::reply()
    : still_data(true)
{
}

void reply::set_file(std::string filename)
{
    file_.open(filename.c_str(), std::ios::in | std::ios::binary);
}

std::vector<boost::asio::const_buffer> reply::to_buffers()
{
    // TODO a ameliore grandement, parce que là c'est vraiment la merde.
    // La merde ! vous dis-je.
    
    // L'ideal : une classe abstraite reply qui construit differente concrete_reply pour chaque type de reply.
    // à étudier.
    
    static char buffer[512];
    std::vector<boost::asio::const_buffer> buffers;
    
    if ( file_.is_open() )
    {
        file_.read(buffer, sizeof(buffer));
        
        if(file_.gcount() < sizeof(buffer))
        {
            still_data = false;
        }
        buffers.push_back(boost::asio::buffer(buffer));
    } else {
        buffers.push_back(boost::asio::buffer(content));
    }
    return buffers;
}

} // namespace server
} // namespace node
