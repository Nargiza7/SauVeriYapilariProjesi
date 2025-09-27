
#ifndef INDEXOUTOFBOUNDS_HPP
#define INDEXOUTOFBOUNDS_HPP
#include "Exception.hpp"

class IndexOutOfBounds : public Exception {
public:

    IndexOutOfBounds(const string &msg) : Exception(msg) {
    }
};


#endif 

