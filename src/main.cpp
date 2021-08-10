#include <cstdio>

#include <iostream>
#include <string>
#include <iterator>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Lexer.h"
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

    std::copy(tokens.cbegin(), tokens.cend(), std::ostream_iterator<syntax::Token>(std::cout));

    return 0;
}
