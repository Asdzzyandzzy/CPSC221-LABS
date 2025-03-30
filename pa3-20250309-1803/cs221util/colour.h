#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <iostream>

/**********************************
* Definitions for coloured output *
**********************************/

namespace cs221util {
    enum Code {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_DEFAULT = 39,
    };
    std::ostream& operator<<(std::ostream& os, Code code) {
        return os << "\033[" << static_cast<int>(code) << "m";
    }
}

#endif