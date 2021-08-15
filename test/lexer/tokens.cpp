#include "test.hpp"

struct TokenTest {
    TokenType expectedType;
    TokenLiteral expectedLiteral;
};

CATCH_TEST_CASE("Simple Lexer", "[lexer]")
{
    string input("=+(){},;");
    Lexer lexer = Lexer(input);

    vector<TokenTest> tests {
        { ASSIGN, "=" },
        { PLUS, "+" },
        { LPAREN, "(" },
        { RPAREN, ")" },
        { LBRACE, "{" },
        { RBRACE, "}" },
        { COMMA, "," },
        { SEMICOLON, ";" },
        { END_OF_FILE, "" },
    };

    CATCH_SECTION("nextToken iterates through tokens")
    {
        for (auto& test : tests) {
            Token token = lexer.nextToken();

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
+=-*/%!
3 < 4.5 > 2

if 5 > 10 then
    return true
else
    return false
end

1+2==3

10 == 10
5 != 10
)"""");
    Lexer lexer = Lexer(input);

    vector<TokenTest> tests {
        { LOCAL, "local" },
        { IDENT, "five" },
        { ASSIGN, "=" },
        { INT, "5" },
        { LOCAL, "local" },
        { IDENT, "ten" },
        { ASSIGN, "=" },
        { INT, "10" },
        { LOCAL, "local" },
        { IDENT, "half" },
        { ASSIGN, "=" },
        { DOUBLE, "0.5" },
        { LOCAL, "local" },
        { IDENT, "add" },
        { ASSIGN, "=" },
        { FUNCTION, "function" },
        { LPAREN, "(" },
        { IDENT, "x" },
        { COMMA, "," },
        { IDENT, "y" },
        { RPAREN, ")" },
        { IDENT, "x" },
        { PLUS, "+" },
        { IDENT, "y" },
        { END, "end" },
        { LOCAL, "local" },
        { IDENT, "result" },
        { ASSIGN, "=" },
        { IDENT, "add" },
        { LPAREN, "(" },
        { IDENT, "five" },
        { COMMA, "," },
        { IDENT, "ten" },
        { RPAREN, ")" },
        { PLUS, "+" },
        { ASSIGN, "=" },
        { MINUS, "-" },
        { ASTERISK, "*" },
        { SLASH, "/" },
        { MODULO, "%" },
        { BANG, "!" },
        { INT, "3" },
        { LT, "<" },
        { DOUBLE, "4.5" },
        { GT, ">" },
        { INT, "2" },
        { IF, "if" },
        { INT, "5" },
        { GT, ">" },
        { INT, "10" },
        { THEN, "then" },
        { RETURN, "return" },
        { TRUE, "true" },
        { ELSE, "else" },
        { RETURN, "return" },
        { FALSE, "false" },
        { END, "end" },
        { INT, "1" },
        { PLUS, "+" },
        { INT, "2" },
        { EQ, "==" },
        { INT, "3" },
        { INT, "10" },
        { EQ, "==" },
        { INT, "10" },
        { INT, "5" },
        { NOT_EQ, "!=" },
        { INT, "10" },
        { END_OF_FILE, "" },
    };

    CATCH_SECTION("nextToken iterates through tokens")
    {
        for (auto& test : tests) {
            Token token = lexer.nextToken();

            CATCH_REQUIRE(token.Type == test.expectedType);
            CATCH_REQUIRE(token.Literal == test.expectedLiteral);
        }
    }
}
