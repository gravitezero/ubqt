//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>

#include "../protocole.hpp"

namespace node {
namespace server {

class request
{
public:

    request();
    setRequestType(CommandCode);

protected:

    CommandCode command;
    std::string value;


};

} // namespace server
} // namespace node

#endif // REQUEST_HPP
