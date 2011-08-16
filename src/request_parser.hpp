//
// request_parser.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>
#include "protocole.hpp"

namespace node {
namespace server {

struct request;

/// Parser for incoming requests.
class request_parser
{
public:
  /// Construct ready to parse the request method.
  request_parser();

  /// Reset to initial parser state.
  void reset();

  /// Parse some data. The tribool return value is true when a complete request
  /// has been parsed, false if the data is invalid, indeterminate when more
  /// data is required. The InputIterator return value indicates how much of the
  /// input has been consumed.
  
  boost::tuple<boost::tribool, char*> parse(request& req,
      char* begin, char* end);

    // TODO k, pour l'instant, tête de bite, c'est un workaround de gobelin.
    // Plus tard, ICI, il y'auras une fonction de parse qui poutre du poney.

private:

};

} // namespace server
} // namespace node

#endif // REQUEST_PARSER_HPP
