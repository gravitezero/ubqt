//
// reply_file.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <string>
#include <boost/lexical_cast.hpp>

#include "reply_file.hpp"

namespace node {
namespace server {

reply_file::reply_file(std::string content)
    : abstract_reply(),
      file_(content.c_str(), std::ios::in | std::ios::binary)
{
}

void reply_file::set_content(std::string content)
{
    if( !file_.is_open() )
        file_.open(content.c_str(), std::ios::in | std::ios::binary);
}

std::vector<boost::asio::const_buffer> reply_file::to_buffers()
{
    // TODO a ameliore grandement, parce que là c'est vraiment la merde.
    // La merde ! vous dis-je.
    
    static char buffer[300];
    std::vector<boost::asio::const_buffer> buffers;
    
    if ( file_.is_open() )
    {
        file_.read(buffer, sizeof(buffer));
        
        if(file_.gcount() < sizeof(buffer))
        {
            still_data = false;
        }
        buffers.push_back(boost::asio::buffer(buffer));
        // TODO ICI on a une erreur du au fait que lorsque le buffer est lu pour la derniere fois, il n'est pas vidé, il reste donc le contenu de la fois precedente a la fin du contenu courant.
        // DONC ON EST DANS LA MERDE !! Cela dit, si on change d'un vecteur de buffer vers un buffer simple, ou un vecteur simple, on aura plus se probleme, je pense, j'èspère ...
    }
    return buffers;
}

} // namespace server
} // namespace node
