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

int main(int argc, char* argv[])
{
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

        //sleep(3);
        
        /// Start connection
        s.add_connection(host, port, reqCode);

        s.join();

    }
        catch (std::exception& e)
    {
    std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}

