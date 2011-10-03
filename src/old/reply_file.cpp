//
// reply_file.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <string>
#include <boost/lexical_cast.hpp>

#include "reply_file.hpp"

namespace node {
namespace server {

reply_file::reply_file(std::string content)
    : abstract_reply(),
      file_(content.c_str(), std::ios::in | std::ios::binary)
{
}

void reply_file::set_content(std::string content)
{
    if( !file_.is_open() )
        file_.open(content.c_str(), std::ios::in | std::ios::binary);
}

std::vector<boost::asio::const_buffer> reply_file::to_buffers()
{
    static boost::array<char, 300> buffer;
    std::vector<boost::asio::const_buffer> buffers;
    
    if ( file_.is_open() )
    {
        file_.read(buffer.begin(), sizeof(buffer));
        
        if(file_.gcount() < sizeof(buffer))
        {
            still_data = false;
        }
        buffers.push_back(boost::asio::buffer(buffer, file_.gcount()));
        // TODO check changer un vector de buffer vers un buffer simple
    }
    return buffers;
}

} // namespace server
} // namespace node
