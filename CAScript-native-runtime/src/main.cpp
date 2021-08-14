#include <cstdio>

#include <iostream>
#include <string>
#include <iterator>
#include <colored.h>

#ifdef _WIN32

#include <Windows.h>

#endif

#include "syntax/Lexer.h"
#include "syntax/Parser.h"
#include <runtime/Evaluator.h>
#include <binding/Binder.h>

using namespace cascript;

static void printTree(syntax::SyntaxNode *node, std::string indent = "", bool is_last = true);

int main() {
    auto show_parse_tree = false;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    for (;;) {
        std::cout << cld::fg(cld::Color::MAGENTA) << "> " << cld::reset;

        std::string source_input;
        std::getline(std::cin, source_input);

        if (source_input == ":exit") {
            break;
        } else if (source_input == ":cls") {
            std::cout << "\033[2J\033[1;1H";
        } else if (source_input == ":show tree") {
            show_parse_tree = true;
        } else {
            syntax::Lexer lexer(source_input);
            auto tokens = lexer.lex();

            syntax::Parser parser(tokens);

            auto expression = parser.parse();

            if (show_parse_tree) {
                printTree(static_cast<syntax::SyntaxNode *>(expression.get()));
            }

            binding::Binder binder{};

            auto bound_expression = binder.bindExpression(std::move(expression));

            runtime::Evaluator evaluator(*bound_expression);
            auto callback = evaluator.eval();

            if (auto b = any_cast<bool>(&callback)) {
                std::cout << std::boolalpha << *b << std::endl;
            } else if (auto ll = any_cast<double>(&callback)) {
                std::cout << *ll << std::endl;
            }
        }
    }

    return 0;
}

static void printTree(syntax::SyntaxNode *node, std::string indent, bool is_last) {
    std::cout << indent << (is_last ? "└── " : "├── ") << magic_enum::enum_name(node->syntax_type());

    if (auto token = dynamic_cast<syntax::Token *>(node)) {
        std::cout << " " << token->literal << std::endl;
        return;
    }

    std::cout << std::endl;

    indent += is_last ? "    " : "│   ";

    auto children = node->children();
    auto size = children.size();
    auto last = children[size - 1];
    for (auto i = 0; i < size; i++) {
        printTree(children[i], indent, last == children[i]);
    }
}
