//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "request_handler.hpp"
#include "request.hpp"

namespace node {
namespace server {

std::vector<std::pair<std::string, std::string> > listeners;
int information = 0;

request_handler::request_handler(const std::string& root_path)
    : file_provider_(root_path)
{
}

abstract_reply_ptr request_handler::handle_request(const request& req)
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
    
  case REGISTER_LISTENER:
    return registerListener(req);

  default:
    return abstract_reply::create("BAD COMMAND REQUEST");
  
  }
}

abstract_reply_ptr request_handler::getTableHandle(const request& req)
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

abstract_reply_ptr request_handler::submitValueHandle(const request& rep)
{
    /// here we should submit the value :
    /// 
    /// it means :  Merge the old value with the new one.
    ///             Ack the new value.
    ///             gathering all listeners to send them the new value.
    ///             keep the modifictation in the history for later listeners
    ///             keep the top version for each listener, to send later modification.

    // TODO the handler for the information.
    // TODO the client side library.
    
    /// Now I'm going to implement this here, but I will move it to the new information handler later.
    
    // Merge the old value, with the new one.
    ++information;

    //for each( std::pair<std::string, std::string> listener in listeners )
    {
        // send new value to listener
        // TODO here we have to make a new connection for handeling the connection with the listener.
    }
    
    // Ack the new value.
    return abstract_reply::create("Submited Value");
}

abstract_reply_ptr request_handler::ackValueHandle(const request& req)
{
    return abstract_reply::create("Ack Value");
}

abstract_reply_ptr request_handler::requestValueHandle(const request& req)
{
    return abstract_reply::create("protocole.hpp");
}

abstract_reply_ptr request_handler::refuseValueHandle(const request& req)
{
    return abstract_reply::create("Refuse Value");
}

abstract_reply_ptr request_handler::registerListener(const request& req)
{
    // Let's say e have a handler for information, here we would actually register the listener in the database.
    //TODO listeners.push_back(new std::pair("localhost","81"));
    
    return abstract_reply::create("Register Listener");
}
} // namespace server
} // namespace node
