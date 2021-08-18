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
        { TokenType::ASSIGN, "=" },
        { TokenType::PLUS, "+" },
        { TokenType::LPAREN, "(" },
        { TokenType::RPAREN, ")" },
        { TokenType::LBRACE, "{" },
        { TokenType::RBRACE, "}" },
        { TokenType::COMMA, "," },
        { TokenType::SEMICOLON, ";" },
        { TokenType::END_OF_FILE, "" },
    };

    CATCH_SECTION("nextToken iterates through tokens")
    {
        for (auto& test : tests) {
            Token token = lexer.nextToken();

            CATCH_REQUIRE(token.type == test.expectedType);
            CATCH_REQUIRE(token.literal == test.expectedLiteral);
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
        { TokenType::LOCAL, "local" },
        { TokenType::IDENT, "five" },
        { TokenType::ASSIGN, "=" },
        { TokenType::INT, "5" },
        { TokenType::LOCAL, "local" },
        { TokenType::IDENT, "ten" },
        { TokenType::ASSIGN, "=" },
        { TokenType::INT, "10" },
        { TokenType::LOCAL, "local" },
        { TokenType::IDENT, "half" },
        { TokenType::ASSIGN, "=" },
        { TokenType::DOUBLE, "0.5" },
        { TokenType::LOCAL, "local" },
        { TokenType::IDENT, "add" },
        { TokenType::ASSIGN, "=" },
        { TokenType::FUNCTION, "function" },
        { TokenType::LPAREN, "(" },
        { TokenType::IDENT, "x" },
        { TokenType::COMMA, "," },
        { TokenType::IDENT, "y" },
        { TokenType::RPAREN, ")" },
        { TokenType::IDENT, "x" },
        { TokenType::PLUS, "+" },
        { TokenType::IDENT, "y" },
        { TokenType::END, "end" },
        { TokenType::LOCAL, "local" },
        { TokenType::IDENT, "result" },
        { TokenType::ASSIGN, "=" },
        { TokenType::IDENT, "add" },
        { TokenType::LPAREN, "(" },
        { TokenType::IDENT, "five" },
        { TokenType::COMMA, "," },
        { TokenType::IDENT, "ten" },
        { TokenType::RPAREN, ")" },
        { TokenType::PLUS, "+" },
        { TokenType::ASSIGN, "=" },
        { TokenType::MINUS, "-" },
        { TokenType::ASTERISK, "*" },
        { TokenType::SLASH, "/" },
        { TokenType::MODULO, "%" },
        { TokenType::BANG, "!" },
        { TokenType::INT, "3" },
        { TokenType::LT, "<" },
        { TokenType::DOUBLE, "4.5" },
        { TokenType::GT, ">" },
        { TokenType::INT, "2" },
        { TokenType::IF, "if" },
        { TokenType::INT, "5" },
        { TokenType::GT, ">" },
        { TokenType::INT, "10" },
        { TokenType::THEN, "then" },
        { TokenType::RETURN, "return" },
        { TokenType::TRUE, "true" },
        { TokenType::ELSE, "else" },
        { TokenType::RETURN, "return" },
        { TokenType::FALSE, "false" },
        { TokenType::END, "end" },
        { TokenType::INT, "1" },
        { TokenType::PLUS, "+" },
        { TokenType::INT, "2" },
        { TokenType::EQ, "==" },
        { TokenType::INT, "3" },
        { TokenType::INT, "10" },
        { TokenType::EQ, "==" },
        { TokenType::INT, "10" },
        { TokenType::INT, "5" },
        { TokenType::NOT_EQ, "!=" },
        { TokenType::INT, "10" },
        { TokenType::END_OF_FILE, "" },
    };

    CATCH_SECTION("nextToken iterates through tokens")
    {
        for (auto& test : tests) {
            Token token = lexer.nextToken();

            CATCH_REQUIRE(token.type == test.expectedType);
            CATCH_REQUIRE(token.literal == test.expectedLiteral);
        }
    }
}
