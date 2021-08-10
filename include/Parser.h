//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_PARSER_H
#define COLLAGE_CPP_PARSER_H

#include <vector>

#include "Token.h"
#include "ExpressionSyntax.h"

namespace collage::syntax {
    class Parser {
    private:
        std::vector<Token> tokens;
        size_t pos = 0;
    public:
        explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

        Token peek(size_t offset);

        Token match(TokenType type);

        Token next();

        Token current() {
            return peek(0);
        };

        ExpressionSyntax parse();

        ExpressionSyntax parseExpression();

        ExpressionSyntax parsePrimaryExpression();
    };
}

#endif //COLLAGE_CPP_PARSER_H
