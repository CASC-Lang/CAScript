#include <cstdio>

#include <iostream>
#include <string>
#include <iterator>

#ifdef _WIN32

#include <Windows.h>
#include <Evaluator.h>

#endif

#include "BinaryExpression.h"
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
    syntax::Evaluator evaluator(*expression);
    auto callback = evaluator.eval();

    if (auto b = any_cast<bool>(&callback)) {
        std::cout << std::boolalpha << *b << std::endl;
    } else if (auto ll = any_cast<double>(&callback)) {
        std::cout << *ll << std::endl;
    }

    return 0;
}
