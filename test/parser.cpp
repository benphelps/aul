#include "test.hpp"

using namespace Aul::AST;

struct StatementTest {
    TokenLiteral expectedLiteral;
    string expectedName;
};

void testStatement(StatementTest test, Statement* statement)
{
    CATCH_REQUIRE(true);
}

void testStatement(StatementTest test, LocalStatement* statement)
{
    CATCH_REQUIRE(statement->token.type == TokenType::LOCAL);
    CATCH_REQUIRE(statement->name.value == test.expectedName);
}

CATCH_TEST_CASE("Test Local Statement", "[parser]")
{
    string input(R""""(
local five = 5;
local ten = 10;
local pi = 3.14159;
)"""");

    Lexer lexer = Lexer(input);
    Parser parser = Parser(lexer);
    Program program = parser.parseProgram();

    CATCH_REQUIRE(parser.errors.size() == 0);
    CATCH_REQUIRE(program.statements.size() == 3);

    vector<StatementTest> tests {
        { "local", "five" },
        { "local", "ten" },
        { "local", "pi" },
    };

    for (size_t i = 0; i < tests.size(); i++) {
        LocalStatement* statement = (LocalStatement*) program.statements[i];
        StatementTest test = tests[i];
        testStatement(test, statement);
    }
}


CATCH_TEST_CASE("Test Local Statement Errors", "[parser]")
{
    string input(R""""(
local a 10;
local = 10;
)"""");

    Lexer lexer = Lexer(input);
    Parser parser = Parser(lexer);
    Program program = parser.parseProgram();

    CATCH_REQUIRE(parser.errors.size() == 2);
}
