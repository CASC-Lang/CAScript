//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_PARSER_H
#define COLLAGE_CPP_PARSER_H

#include <utility>
#include <vector>
#include <memory>
#include <ranges>

#include "Token.h"
#include "ExpressionSyntax.h"

namespace cascript::syntax {
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

        std::unique_ptr<syntax::ExpressionSyntax> parse();

        std::unique_ptr<syntax::ExpressionSyntax> parseExpression(unsigned parent_precedence = 0);

        std::unique_ptr<syntax::ExpressionSyntax> parsePrimaryExpression();
    };
}

#endif //COLLAGE_CPP_PARSER_H
