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
#include "request.hpp"

int main(int argc, char* argv[])
{

    std::string command;
    std::string op;
    std::string host;
    std::string port;
    
    try
    {
        // Check command line arguments.
        if (argc != 4)
            {
                std::cerr << "Usage: server <address> <port> <path>\n";
                std::cerr << "  For IPv4, try:\n";
                std::cerr << "    receiver 0.0.0.0 80 .\n";
                std::cerr << "  For IPv6, try:\n";
                std::cerr << "    receiver 0::0 80 .\n";
                return 1;
            }

        // Initialise the server.
        node::server::server s(argv[1], argv[2], argv[3]);

        // Run the server
        s.run();
        std::cout << "Running server\n";
        
        std::cout << "--------\n";
        
        do {            
            op.clear();
            std::cout << "1 add a connection : add host port\n";
            std::cout << "2 quit\n\n";
            
            std::cin >> op;
            
            if ( op.compare("add") == 0 )
            {
                std::cin >> host >> port;
                s.add_connection(host, port, node::server::REQUEST_VALUE);
            }
            
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            //std::cin.clear();
            host.clear();
            port.clear();
            
        } while ( op.compare("quit") != 0 );
        std::cout << "quitting\n\n";

        //sleep(3);
        
        std::cout << "Request Value" << std::endl;
        
        char c;
        std::cin >> c;
        std::cout << "Adding connection" << std::endl;
        /// Start connection

        s.add_connection("localhost", "8080", node::server::REQUEST_VALUE);
        std::cout << "Connection added" << std::endl;

        s.join();

    }
        catch (std::exception& e)
    {
    std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}

