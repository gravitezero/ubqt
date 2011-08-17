//
// file_provider.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
//#include <signal.h>

namespace node {
namespace server {

file_provider::file_provider(const std::string& path)
    : path(path)
{
    
}

int file_provider::getFile(const std::string& name, std::string& file)
{
    std::string full_path = path + name;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    
    char buf[512];
    
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        file.append(buf, is.gcount());
    
    return 0;
}

//const boost::array<std::string> file_provider::getListFile()
const std::vector<std::string> file_provider::getListFile()
{
    boost::filesystem::path directory = path;
    //boost::array<std::string, 10> array;
    std::vector<std::string> files;

    if ( boost::filesystem::exists(directory) )
    {
        boost::filesystem::directory_iterator end;
        for (boost::filesystem::directory_iterator iter(directory) ; iter != end ; ++iter )
        {
            if ( !boost::filesystem::is_directory(*iter) )
            {
                files.push_back(boost::filesystem::basename(iter->path()));
            }
        }
    }
    
    return files;
}

} // namespace server
} // namespace node
