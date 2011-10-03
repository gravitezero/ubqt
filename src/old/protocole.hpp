//
// protocole.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Etienne Brodu (etienne dot brodu at insa dash lyon dot fr)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PROTOCOLE_H
#define PROTOCOLE_H

enum CommandCode {
    GET_TABLE,
    SUBMIT_VALUE,
    ACK_VALUE,
    REQUEST_VALUE,
    REFUSE_SUBMIT,
    REGISTER_LISTENER
};

/*class node {

    public:
        int registerListener(String listenerName);
        int registerNode(String nodeName);
        
        int submitChange(int info);
        
        int listen();

    
    private:
        int info;

};*/

#endif // PROTOCOLE_H
