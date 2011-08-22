//
// abstract_reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
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
    virtual void set_content(std::string content) = 0;
    static boost::shared_ptr<abstract_reply> create(std::string content);
    
    bool still_data;

protected:

    abstract_reply(); // To keep it abstract, I think ... TODO check this

};

} // namespace server
} // namespace node

#endif // ABSTRACT_REPLY_HPP
