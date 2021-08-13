//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_TOKEN_H
#define COLLAGE_CPP_TOKEN_H

#include <utility>
#include <iterator>
#include <iostream>

#include <magic_enum.hpp>

#include "TokenType.h"
#include "SyntaxNode.h"

namespace cascript::syntax {
    struct Token : public SyntaxNode {
        Token(TokenType type, char literal) : type(type), literal(1, literal) {}

        Token(TokenType type, std::string literal) : type(type), literal(std::move(literal)) {}

        TokenType type;
        std::string literal;

        SyntaxType syntax_type() const final {
            return SyntaxType::Token;
        };

        std::vector<SyntaxNode*> children() final {
            return std::vector<SyntaxNode*> {};
        };
    };

    inline std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "<syntax_type:" << magic_enum::enum_name(token.type) << "/literal:" << token.literal << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_TOKEN_H
