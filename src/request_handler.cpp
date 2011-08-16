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
    getTableHandle(req, rep);
    break;
  
  case SUBMIT_VALUE:
    submitValueHandle(req, rep);
    break;
      
  case ACK_VALUE:
    ackValueHandle(req, rep);
    break;
      
  case REQUEST_VALUE:  
    requestValueHandle(req, rep);
    break;
  
  case REFUSE_SUBMIT:
    refuseValueHandle(req, rep);
    break;
  
  default:
    rep.content.append("BAD COMMAND REQUEST");
  
  }
}

void request_handler::getTableHandle(const request& req, reply& rep)
{
    rep.content.append("Get Table");
}

void request_handler::submitValueHandle(const request& req, reply& rep)
{
    rep.content.append("Submit Value");
}

void request_handler::ackValueHandle(const request& req, reply& rep)
{
    rep.content.append("Ack Value");
}

void request_handler::requestValueHandle(const request& req, reply& rep)
{
    rep.content.append("Request Value");
}

void request_handler::refuseValueHandle(const request& req, reply& rep)
{
    rep.content.append("Refuse Value");
}
} // namespace server
} // namespace node
