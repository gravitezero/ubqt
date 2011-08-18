//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REPLY_HPP
#define REPLY_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

namespace node {
namespace server {

/// A reply to be sent to a client.
/*struct reply
{

    /// The content to be sent in the reply.
    std::string content;

    /// Convert the reply into a vector of buffers. The buffers do not own the
    /// underlying memory blocks, therefore the reply object must remain valid and
    /// not be changed until the write operation has completed.
    std::vector<boost::asio::const_buffer> to_buffers();
};*/

// TODO Do it templated
class reply
{
public:
    reply();
    std::vector<boost::asio::const_buffer> to_buffers();
    void set_file(std::string filename);
    
    bool still_data;
    std::string content;
    
private:
    //std::string content;
    std::ifstream file_;

};

} // namespace server
} // namespace node

#endif // REPLY_HPP
