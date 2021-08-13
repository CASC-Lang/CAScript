//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_LEXER_H
#define COLLAGE_CPP_LEXER_H

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "Token.h"

namespace cascript::syntax {
    class Lexer {
    private:
        std::string source;
        std::string::size_type pos = 0;
    public:
        explicit Lexer(std::string source) : source(std::move(source)) {}

        std::vector<Token> lex();
    };
}

#endif //COLLAGE_CPP_LEXER_H
