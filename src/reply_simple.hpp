//
// reply_simple.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REPLY_SIMPLE_HPP
#define REPLY_SIMPLE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

#include "abstract_reply.hpp"

namespace node {
namespace server {

class reply_simple : public abstract_reply
{
public:
    reply_simple();

    std::vector<boost::asio::const_buffer> to_buffers();
    void set_content(std::string content); // TODO ICI template, une seule methode set_info pour faire pointer la reply vers ressource que tu veux envoyer.
    
private:
    std::string content;
        
        
};

} // namespace server
} // namespace node

#endif // REPLY_FILE_HPP
