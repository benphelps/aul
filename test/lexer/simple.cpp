#include "test.hpp"

struct TokenTest {
    Lexer::TokenType expectedType;
    Lexer::TokenLiteral expectedLiteral;
};

TEST_CASE("Lexer", "[lexer]" )
{
    string input("=+(){},;");
    Lexer::Lexer lexer = Lexer::Lexer(input);

    vector<TokenTest> tests {
        { Lexer::ASSIGN, "=" },
        { Lexer::PLUS, "+" },
        { Lexer::LPAREN, "(" },
        { Lexer::RPAREN, ")" },
        { Lexer::LBRACE, "{" },
        { Lexer::RBRACE, "}" },
        { Lexer::COMMA, "," },
        { Lexer::SEMICOLON, ";" },
        { Lexer::END_OF_FILE, "" },
    };

    SECTION("nextToken iterates through tokens") {
        for (auto &test : tests)
        {
            Lexer::Token token = lexer.nextToken();

            REQUIRE(token.Type == test.expectedType);
            REQUIRE(token.Literal == test.expectedLiteral);
        }
    }
}
