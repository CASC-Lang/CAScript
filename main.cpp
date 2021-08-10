#include <iostream>
#include <string>
#include <windows.h>
#include <cstdio>
#include "src/Lexer.h"

using namespace collage;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IONBF, 0);

    std::string source_input;
    getline(std::cin, source_input);

    syntax::Lexer lexer(source_input);
    auto tokens = lexer.lex();

    for (auto & token : tokens)
        std::cout << token << ", ";

    return 0;
}
