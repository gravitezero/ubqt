//
// events_service.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Etienne Brodu (etienne dot brodu  at insa dash lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef EVENTS_SERVICE_HPP
#define EVENTS_SERVICE_HPP

#include <queue>
#include <string>



namespace node {
namespace events_service {

class events_server
{
public:
    void run();

    // for a link, a set of events and callback functions associated should be set up.
    // Let's do something really good with some boost::bind
    int add_link(link_id id, map<event, functions>);
    
    // a link is actually a connection, so let's reuse this old class
    int remove_link(link_id id);
    
    // when an event is thrown, the events_service will call the associated function.
    int throw_event(link_id id, event ev);

private:
    
    std::queue<event> events;
    std::vector<link> links;
    
};

} // namespace events_service
} // namespace node

#endif // EVENTS_SERVICE_HPP
