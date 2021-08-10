//
// Created by User on 8/10/2021.
//

#include <utility>
#include <iterator>
#include "../lib/magic_enum.hpp"
#include "TokenType.h"

#ifndef COLLAGE_CPP_TOKEN_H
#define COLLAGE_CPP_TOKEN_H

namespace collage::syntax {
    class Token {
    public:
        Token(enum TokenType type, std::string literal) : type(type), literal(std::move(literal)) {}

        enum TokenType type;
        std::string literal;
    };

    std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "<type:" << magic_enum::enum_name(token.type) << "/literal:" << token.literal << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_TOKEN_H
