//
// data_manager.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

        int data_manager::get_data( int id, std::string& data)
        {
            data = data_;
        }
        
        int data_manager::append_data( int id, std::string data )
        {
            data_.append(data);
        }
        
