//
// communication_handler.cpp
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
#include "communication_handler.hpp"
#include "request.hpp"
#include "reply.hpp"

namespace node {
namespace server {

std::vector<std::pair<std::string, std::string> > listeners;
int information = 0;

communication_handler::communication_handler()
{
    data_manager_ = data_manager::get_instance();
}

int communication_handler::handle_request(request* const req, reply& rep)
{ 

    // TODO Ici, check le meta switch
    // Completement remplacer ce pattern :
    // à la place, on appelle req pour faire le job.
    // communication_handler n'est alors plus necessaire.
  
      switch(req->request_code_) //TODO VISITOR PATTERN
      {
          case REQUEST_VALUE:  
            return requestValueHandle(req, rep);
            
          /*case GET_TABLE:
            return getTableHandle(req, req);

          case SUBMIT_VALUE:
            return submitValueHandle(req);
            
          case REGISTER_LISTENER:
            return registerListener(req);*/

          //default:
            //return reply::create("BAD COMMAND REQUEST");  //TODO à reimplementer
      
      }
      
      return 0;
}

int communication_handler::handle_reply(reply* const rep, request& req) // TODO essayer de passer reply par reference, et non par pointeur.
{

    // TODO make this intern of the reply.
      switch(rep->reply_code_)
      {
          case SEND_VALUE:
            return sendValueHandle(rep, req);   
               
          /*case SEND_TABLE:
            return sendTableHandle(rep);

          case REQUEST_VALUE:
            return requestValueHandle(rep);

          case REFUSE_SUBMIT:
            return refuseValueHandle(rep);*/

          //default:
            //return reply::create("BAD COMMAND REPLY"); //TODO à reimplementer
      
      }
      
      return 0;
}

/*
getTableHandle(req);
requestValueHandle(req);
submitValueHandle(req);
registerListener(req);

sendTableHandle(rep);
sendValueHandle(rep);
requestValueHandle(rep);
refuseValueHandle(rep);
*/

/// REQUEST HANDLER

int communication_handler::requestValueHandle(const request* const req, reply& rep)
{
    std::string str;
    rep.reply_code_ = SEND_VALUE;
    data_manager_.get_data(str&);
    rep.value = str;
    //rep.value.assign("42");
    
    return 0;
}

int communication_handler::sendValueHandle(const reply* const rep, request& req)
{
    data_manager_.append_data(rep->value);
    //std::cout << rep->value << std::endl;
    
    return -1;
}


















/*

abstract_reply_ptr communication_handler::getTableHandle(const request& req)
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

abstract_reply_ptr communication_handler::submitValueHandle(const request& rep)
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

    for(std::vector<std::pair<std::string, std::string> >::iterator listener = listeners.begin(); listener != listeners.end(); ++listener) {
        // std::cout << *listener; ... 
    }

    
    // Ack the new value.
    return abstract_reply::create("Submited Value");
}

abstract_reply_ptr communication_handler::registerListener(const request& req)
{
    // Let's say e have a handler for information, here we would actually register the listener in the database.
    listeners.push_back(std::make_pair("localhost", "81"));
    
    return abstract_reply::create("Register Listener");
}

/// REPLY HANDLER

abstract_reply_ptr communication_handler::sendTableHandle(const request& req)
{
    return abstract_reply::create("Send Table");
}

abstract_reply_ptr communication_handler::requestValueHandle(const request& req)
{
    return abstract_reply::create("Request Value");
}

abstract_reply_ptr communication_handler::refuseValueHandle(const request& req)
{
    return abstract_reply::create("Refuse Value");
}
*/
} // namespace server
} // namespace node
