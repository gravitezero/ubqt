//
// reply_file.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REPLY_FILE_HPP
#define REPLY_FILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

#include "abstract_reply.hpp"

namespace node {
namespace server {

class reply_file
    : public abstract_reply
{
public:
    reply_file(std::string content);

    std::vector<boost::asio::const_buffer> to_buffers();
    void set_content(std::string filename);
    
private:
    std::ifstream file_;
        
        
};

} // namespace server
} // namespace node

#endif // REPLY_FILE_HPP
