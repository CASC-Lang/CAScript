//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include <utility>
#include <iterator>

#include <magic_enum.hpp>

#include "TokenType.h"

#ifndef COLLAGE_CPP_TOKEN_H
#define COLLAGE_CPP_TOKEN_H

namespace collage::syntax {
    struct Token {
        Token(TokenType type, char literal) : type(type), literal(1, literal) {}
        Token(TokenType type, std::string literal) : type(type), literal(std::move(literal)) {}

        TokenType type;
        std::string literal;
    };

    inline std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "<type:" << magic_enum::enum_name(token.type) << "/literal:" << token.literal << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_TOKEN_H
