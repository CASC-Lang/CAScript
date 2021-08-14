#include <gtest/gtest.h>

#include <string>

#include <syntax/Lexer.h>
#include <binding/Binder.h>
#include <syntax/Parser.h>
#include <runtime/Evaluator.h>

using namespace cascript;

template<typename T>
T eval(std::string source) {
    syntax::Lexer lexer(std::move(source));
    syntax::Parser parser(lexer.lex());
    binding::Binder binder{};
    runtime::Evaluator evaluator(*binder.bindExpression(parser.parse()));
    return std::any_cast<T>(evaluator.eval());
}

TEST(EvalTest, LiteralTest) {
    EXPECT_EQ(eval<bool>("true"), true);
    EXPECT_EQ(eval<bool>("false"), false);
}
