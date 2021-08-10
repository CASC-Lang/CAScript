#include <cstdio>

#include <iostream>
#include <string>
#include <iterator>

#ifdef _WIN32
#include <Windows.h>
#include <BinaryExpression.h>
#include <magic_enum.hpp>

#endif

#include "Lexer.h"
#include "Parser.h"
#include "Token.h"

using namespace collage;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    std::string source_input;
    std::getline(std::cin, source_input);

    syntax::Lexer lexer(source_input);
    auto tokens = lexer.lex();

    syntax::Parser parser(tokens);

    auto expression = parser.parse();

    std::cout << magic_enum::enum_name(expression->type()) << std::endl;

    if (expression->type() == syntax::SyntaxType::Binary) {
        auto expr = std::static_pointer_cast<syntax::BinaryExpression>(expression);
        std::cout << expr.get() << std::endl;
    }

    return 0;
}
