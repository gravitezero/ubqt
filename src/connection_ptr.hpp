//
// connection_ptr.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONNECTION_PTR_HPP
#define CONNECTION_PTR_HPP

namespace node {
namespace server {

    template <class Incoming, class Outcoming> class connection;

    typedef connection<request, reply> listening_connection;
    typedef connection<reply, request> client_connection;

    typedef boost::shared_ptr<listening_connection> listening_connection_ptr;
    typedef boost::shared_ptr<client_connection> client_connection_ptr;

} // namespace server
} // namespace node

#endif //CONNECTION_PTR_HPP
