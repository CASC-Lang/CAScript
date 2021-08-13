//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_TOKENTYPE_H
#define COLLAGE_CPP_TOKENTYPE_H

namespace collage::syntax {
    enum class TokenType {
        Identifier,
        BoolLiteral,
        NumberLiteral,
        OpenParenthesis,
        CloseParenthesis,
        DoubleEqual,
        BangEqual,
        DoubleGreaterThan,
        TripleGreaterThan,
        GreaterThan,
        GreaterEqualThan,
        DoubleLessThan,
        LessThan,
        LessEqualThan,
        DoubleAmpersand,
        Ampersand,
        Caret,
        DoublePipe,
        Pipe,
        Bang,
        Tilde,
        Plus,
        Minus,
        Star,
        DoubleStar,
        Slash,
        DoubleSlash,
        Percent,
    };

    constexpr unsigned unary_precedence(TokenType token) {
        switch (token) {
            case TokenType::Tilde:
            case TokenType::Bang:
            case TokenType::Plus:
            case TokenType::Minus:
                return 11;
            default:
                return 0;
        }
    }

    constexpr unsigned binary_precedence(TokenType token) {
        switch (token) {
            case TokenType::DoublePipe:
                return 1;
            case TokenType::DoubleAmpersand:
                return 2;
            case TokenType::Pipe:
                return 3;
            case TokenType::Caret:
                return 4;
            case TokenType::Ampersand:
                return 5;
            case TokenType::DoubleEqual:
            case TokenType::BangEqual:
                return 6;
            case TokenType::GreaterThan:
            case TokenType::GreaterEqualThan:
            case TokenType::LessThan:
            case TokenType::LessEqualThan:
                return 7;
            case TokenType::DoubleGreaterThan:
            case TokenType::DoubleLessThan:
                return 8;
            case TokenType::Plus:
            case TokenType::Minus:
                return 9;
            case TokenType::Star:
            case TokenType::Slash:
            case TokenType::DoubleSlash:
            case TokenType::Percent:
                return 10;
            case TokenType::DoubleStar:
                return 12;
            default:
                return 0;
        };
    }
}

#endif //COLLAGE_CPP_TOKENTYPE_H
