//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "server.hpp"
#include "data_manager.hpp"
#include "request.hpp"

int main(int argc, char* argv[])
{

    try
    {
        // Check command line arguments.
        if (argc != 3)
            {
                std::cerr << "Usage: server <address> <port>\n";
                std::cerr << "  For IPv4, try:\n";
                std::cerr << "    receiver 0.0.0.0 80 .\n";
                std::cerr << "  For IPv6, try:\n";
                std::cerr << "    receiver 0::0 80 .\n";
                return 1;
            }

        // Initialise the data_manager
        node::server::data_manager * mgr = node::server::data_manager::get_instance();

        // Initialise the server.
        node::server::server s(argv[1], argv[2]);
        
        mgr->set_server(s);

        // Run the server
        s.run();
        std::cout << "Running server\n";
        std::cout << "--------\n";
        
        std::string op;
        
        do {            
            op.clear();
            std::cout << "get data : get host port\n";
            std::cout << "view data : view\n";
            std::cout << "append to data : append\n";
            std::cout << "quit\n\n";
            
            std::cin >> op;
            
            if ( op.compare("get") == 0 )
            {
                std::string host,port;
                std::cin >> host >> port;
                s.add_connection(host, port, node::server::REQUEST_VALUE);
            }
            else if ( op.compare("view") == 0)
            {
                std::string buffer;
                mgr->get_data(0, buffer);
                std::cout << buffer << std::endl << std::endl;
            }
            else if ( op.compare("append") == 0)
            {
                std::string buffer;
                std::cin >> buffer;
                mgr->append_data(0, buffer);
                std::cout << std::endl;
            }
            
        } while ( op.compare("quit") != 0 );
        std::cout << "quitting\n\n";
        
        s.join();

    }
        catch (std::exception& e)
    {
    std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}

