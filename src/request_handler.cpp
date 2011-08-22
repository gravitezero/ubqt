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
    : file_provider_(root_path)
{
}

boost::shared_ptr<abstract_reply> request_handler::handle_request(const request& req)
{ 

    // TODO Ici, check le meta switch
  
  switch(req.command)
  {  
  case GET_TABLE:
    return getTableHandle(req);
  
  case SUBMIT_VALUE:
    return submitValueHandle(req);
      
  case ACK_VALUE:
    return ackValueHandle(req);

  case REQUEST_VALUE:  
    return requestValueHandle(req);

  case REFUSE_SUBMIT:
    return refuseValueHandle(req);

  default:
    return abstract_reply::create("BAD COMMAND REQUEST");
  
  }
}

boost::shared_ptr<abstract_reply> request_handler::getTableHandle(const request& req)
{
    std::string files_name;
    std::vector<std::string> files = file_provider_.getListFile();
    std::vector<std::string>::iterator iter;
    
    for(iter = files.begin() ; iter != files.end() ; iter++)
    {
        files_name.append(*iter);
        files_name.append("\n");
    }
    
    return abstract_reply::create(files_name);
}

boost::shared_ptr<abstract_reply> request_handler::submitValueHandle(const request& rep)
{
    return abstract_reply::create("Submit Value");
}

boost::shared_ptr<abstract_reply> request_handler::ackValueHandle(const request& req)
{
    return abstract_reply::create("Ack Value");
}

boost::shared_ptr<abstract_reply> request_handler::requestValueHandle(const request& req)
{
    return abstract_reply::create("protocole.hpp");
}

boost::shared_ptr<abstract_reply> request_handler::refuseValueHandle(const request& req)
{
    return abstract_reply::create("Refuse Value");
}
} // namespace server
} // namespace node
