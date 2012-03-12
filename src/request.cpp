//
// request.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace node {
namespace server {

request::request(communication_handler& handler)
    : message(handler)
{
}

int request::handle(reply& rep)
{
    communication_handler_.handle_request(this, rep);
}

int request::parse(char* begin, char* end)
{
    request_code_ = (RequestCode)*begin;
    
    //if (request_code_ == REQUEST_VALUE)
    {
        value.assign(begin, end - begin); // TODO à changer, pas propre.
        std::cout << "value : " << value << std::endl;
    }
    
    return true;
}

std::vector<boost::asio::const_buffer> request::to_buffers()
{
    // TODO a ameliore grandement, parce que là c'est vraiment la merde.
    // La merde ! vous dis-je.
    
    static char buffer[300];
    std::vector<boost::asio::const_buffer> buffers;

    //buffers.push_back(boost::asio::buffer((char)request_code_)) //TODO à corriger
    buffers.push_back(boost::asio::buffer(value));
    still_data = false; // TODO still_data est un moyen vraiment tres mauvais de dire que la transaction est terminé.
    
    std::cout << "sending : " << value << std::endl;
    
    return buffers;
}

} // namespace server
} // namespace node
