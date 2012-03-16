//
// file_provider.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef FILE_PROVIDER_HPP
#define FILE_PROVIDER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <boost/noncopyable.hpp>

namespace node {
namespace server {

/// The class which provide files
class file_provider
    : private boost::noncopyable
{
public:
    /// Construct the provider with the path of the directory containing the files
    explicit file_provider(const std::string& path);

    /// Append the content of the file named name to the string file
    int getFile(const std::string& name, std::string& file);
    
    /// Get the list of available files
    //const boost::array<std::string> getListFile();
    const std::vector<std::string> getListFile();

private:
    std::string path;

};

} // namespace server
} // namespace node

#endif // FILE_PROVIDER_HPP
