//
// data_manager.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "data_manager.hpp"

namespace node {
namespace server {

data_manager* data_manager::instance_ = NULL;

data_manager* data_manager::get_instance()
{
   if (!instance_)   // Only allow one instance of class to be generated.
   instance_ = new data_manager;

   return instance_;
}

data_manager::data_manager()
    :ticket(0)
{
}

void data_manager::set_server(server* srv)
{
    server_ = srv;
}

int data_manager::register_listener(void (*callback)(void))
{
    callback_.insert(callback_pair(++ticket, callback));
}

int data_manager::remove_listener(int id)
{
    callback_.erase(callback_.find(id));
}

int data_manager::get_data( int id, std::string& data)
{
    data = data_;
}

int data_manager::append_data( int id, std::string data )
{
    data_.append(data);
}

} // namespace server
} // namespace node
