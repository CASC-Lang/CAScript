//
// Created by alanj on 8/12/2021.
//

#include "colored.h"

using namespace cld;

#ifdef _WIN32

namespace {
    WORD get_default_attrib() {
        auto console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(console, &buffer_info);
        return buffer_info.wAttributes;
    }
    WORD default_attrib = get_default_attrib();
}

std::ostream& cld::operator<<(std::ostream& lhs, const WindowsAttribFactor& rhs) {
    static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    static WORD curr_attrib = default_attrib;
    rhs.factor(curr_attrib);
    SetConsoleTextAttribute(console, curr_attrib);
    return lhs;
}

extern const WindowsAttribFactor cld::reset = {[](WORD& attrib) { attrib = default_attrib; }};

#endif