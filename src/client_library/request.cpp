//
// request.cpp
// ~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa-lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <string>

#include "request.hpp"

namespace node {
namespace server {

request::request()
{

}


request::setRequestType(CommandCode code){

    //TODO Change the protocol to differentiate request and reply code.

    if(code == GET_TABLE
    || code == SUBMIT_VALUE
    || code == REQUEST_VALUE
    || code == REGISTER_LISTENER)
    {
        this.code = code;
    }
}

} // namespace server
} // namespace node
