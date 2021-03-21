#include "test.hpp"

struct TokenTest {
    Lexer::Token::TokenType expectedType;
    Lexer::Token::TokenLiteral expectedLiteral;
};

CATCH_TEST_CASE("Simple Lexer", "[lexer]")
{
    string input("=+(){},;");
    Lexer::Lexer lexer = Lexer::Lexer(input);

    vector<TokenTest> tests {
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::PLUS, "+" },
        { Lexer::Token::LPAREN, "(" },
        { Lexer::Token::RPAREN, ")" },
        { Lexer::Token::LBRACE, "{" },
        { Lexer::Token::RBRACE, "}" },
        { Lexer::Token::COMMA, "," },
        { Lexer::Token::SEMICOLON, ";" },
        { Lexer::Token::END_OF_FILE, "" },
    };

    CATCH_SECTION("nextToken iterates through tokens")
    {
        for (auto& test : tests) {
            Lexer::Token::Token token = lexer.nextToken();

            CATCH_REQUIRE(token.Type == test.expectedType);
            CATCH_REQUIRE(token.Literal == test.expectedLiteral);
        }
    }
}

CATCH_TEST_CASE("Complete Lexer", "[lexer]")
{
    string input(R""""(
local five = 5
local ten = 10
local half = 0.5

local add = function(x, y)
    x + y
end

local result = add(five, ten)
+=-*/%
3 < 4.5 > 2

if 5 > 10 then
    return true
else
    return false
end
)"""");
    Lexer::Lexer lexer = Lexer::Lexer(input);

    vector<TokenTest> tests {
        { Lexer::Token::LOCAL, "local" },
        { Lexer::Token::IDENT, "five" },
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::INT, "5" },
        { Lexer::Token::LOCAL, "local" },
        { Lexer::Token::IDENT, "ten" },
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::INT, "10" },
        { Lexer::Token::LOCAL, "local" },
        { Lexer::Token::IDENT, "half" },
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::DOUBLE, "0.5" },
        { Lexer::Token::LOCAL, "local" },
        { Lexer::Token::IDENT, "add" },
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::FUNCTION, "function" },
        { Lexer::Token::LPAREN, "(" },
        { Lexer::Token::IDENT, "x" },
        { Lexer::Token::COMMA, "," },
        { Lexer::Token::IDENT, "y" },
        { Lexer::Token::RPAREN, ")" },
        { Lexer::Token::IDENT, "x" },
        { Lexer::Token::PLUS, "+" },
        { Lexer::Token::IDENT, "y" },
        { Lexer::Token::END, "end" },
        { Lexer::Token::LOCAL, "local" },
        { Lexer::Token::IDENT, "result" },
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::IDENT, "add" },
        { Lexer::Token::LPAREN, "(" },
        { Lexer::Token::IDENT, "five" },
        { Lexer::Token::COMMA, "," },
        { Lexer::Token::IDENT, "ten" },
        { Lexer::Token::RPAREN, ")" },
        { Lexer::Token::PLUS, "+" },
        { Lexer::Token::ASSIGN, "=" },
        { Lexer::Token::MINUS, "-" },
        { Lexer::Token::ASTERISK, "*" },
        { Lexer::Token::SLASH, "/" },
        { Lexer::Token::MODULO, "%" },
        { Lexer::Token::INT, "3" },
        { Lexer::Token::LT, "<" },
        { Lexer::Token::DOUBLE, "4.5" },
        { Lexer::Token::GT, ">" },
        { Lexer::Token::INT, "2" },
        { Lexer::Token::IF, "if" },
        { Lexer::Token::INT, "5" },
        { Lexer::Token::GT, ">" },
        { Lexer::Token::INT, "10" },
        { Lexer::Token::THEN, "then" },
        { Lexer::Token::RETURN, "return" },
        { Lexer::Token::TRUE, "true" },
        { Lexer::Token::ELSE, "else" },
        { Lexer::Token::RETURN, "return" },
        { Lexer::Token::FALSE, "false" },
        { Lexer::Token::END, "end" },
        { Lexer::Token::END_OF_FILE, "" },
    };

    CATCH_SECTION("nextToken iterates through tokens")
    {
        for (auto& test : tests) {
            Lexer::Token::Token token = lexer.nextToken();

            CATCH_REQUIRE(token.Type == test.expectedType);
            CATCH_REQUIRE(token.Literal == test.expectedLiteral);
        }
    }
}
