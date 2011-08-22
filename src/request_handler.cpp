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

request_handler::request_handler(const std::string& root_path)
//    : file_provider_(root_path)
{
}

boost::shared_ptr<abstract_reply> request_handler::handle_request(const request& req)
{ 

    // TODO Ici, check le meta switch
  
  switch(req.command)
  {  
  /*
  case GET_TABLE:
    getTableHandle(req, rep);
    break;
  
  case SUBMIT_VALUE:
    submitValueHandle(req, rep);
    break;
      
  case ACK_VALUE:
    ackValueHandle(req, rep);
    break;
    */  
  case REQUEST_VALUE:  
    return requestValueHandle(req);
  /*
  case REFUSE_SUBMIT:
    refuseValueHandle(req, rep);
    break;
  */
  //default:
    //rep.content.append("BAD COMMAND REQUEST");
  
  }
}
/*
void request_handler::getTableHandle(const request& req, reply& rep)
{
    //rep.content.append("Get Table");
    std::vector<std::string> files = file_provider_.getListFile();
    std::vector<std::string>::iterator iter;
    
    for(iter = files.begin() ; iter != files.end() ; iter++)
    {
        rep.content.append(*iter);
        rep.content.append("\n");
    }
}

void request_handler::submitValueHandle(const request& req, reply& rep)
{
    rep.content.append("Submit Value");
}

void request_handler::ackValueHandle(const request& req, reply& rep)
{
    rep.content.append("Ack Value");
}*/

boost::shared_ptr<abstract_reply> request_handler::requestValueHandle(const request& req)
{
    //rep.content.append("Request Value");
    //file_provider_.getFile("reply.hpp", rep.content&);
    return abstract_reply::create("protocole.hpp");
    //rep.set_file("protocole.hpp");
}

/*void request_handler::refuseValueHandle(const request& req, reply& rep)
{
    rep.content.append("Refuse Value");
}*/
} // namespace server
} // namespace node
