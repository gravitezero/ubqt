//
// abstract_reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ABSTRACT_REPLY_HPP
#define ABSTRACT_REPLY_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

namespace node {
namespace server {

// TODO Do it templated
class abstract_reply
{
public:
    //reply(); // TODO see up : Do it template ?
    virtual std::vector<boost::asio::const_buffer> to_buffers() = 0;
    static abstract_reply* create();
    
    bool still_data;

protected:

    abstract_reply(); // To keep it abstract, I think ... TODO check this

};

} // namespace server
} // namespace node

#endif // ABSTRACT_REPLY_HPP
