//
// data_manager.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <string>
#include <map>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
//#include "server.hpp"


namespace node {
namespace server {

class server;

typedef void (*callback)(void);
typedef std::pair<unsigned int, callback> callback_pair;

/// data_manager
class data_manager
{
    public:
    
        static data_manager* get_instance();
    
        void set_server(server& srv);
        
        int register_listener(callback clbk);
        
        int remove_listener(int id);
    
        int get_data( int id, std::string& data);
        
        int append_data( int id, std::string data );
        
    private:        
        data_manager();
        data_manager(data_manager const&){};
        data_manager& operator=(data_manager const&){};
        
        static data_manager* instance_;
        
        /// for debugging purpose, instead of a database, we use a single string to hold information.
        std::string data_;
        
        std::map<unsigned int, callback> callback_;
        unsigned int ticket;
        server *server_;
};

} // namespace server
} // namespace node

#endif // DATA_MANAGER_HPP
