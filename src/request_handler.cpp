//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace node {
namespace server {

request_handler::request_handler()
{
}

void request_handler::handle_request(const request& req, reply& rep)
{ 

    // TODO Ici, un switch case pour traiter toutes les requetes
  
  std::cout << req.command << std::endl;
  
  switch(req.command)
  {  
  case GET_TABLE:
    rep.content.append("You asked for the table, right ?");
    break;
  
  case SUBMIT_VALUE:
    rep.content.append("I hear you, you want to submit something");
    break;
      
  case ACK_VALUE:
    rep.content.append("Oh ... right, you received this stuff");
    break;
      
  case REQUEST_VALUE:  
    rep.content.append("You asked for the info ... well .. I don't have it yet");
    break;
  
  case REFUSE_SUBMIT:
    rep.content.append("What ? youtalkintome ?");
    break;
  
  default:
    rep.content.append("BAD COMMAND REQUEST");
  
  }
}

} // namespace server
} // namespace node
