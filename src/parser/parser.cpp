#include "parser/parser.hpp"

#include <utility>

namespace Aul
{
    Parser::Parser(::Lexer lexer)
        : lexer(std::move(lexer))
    {
    }

    void Parser::nextToken()
    {
        this->currentToken = this->peekToken;
        this->peekToken = this->lexer.nextToken();
    }

    Program Parser::parseProgram()
    {
        Program program;

        while (this->currentTokenIsNot(TokenType::END_OF_FILE)) {
            Statement* statement = this->parseStatement();

            if (statement) {
                program.statements.push_back(statement);
            }

            this->nextToken();
        }

        return program;
    }

    Statement* Parser::parseStatement()
    {
        switch (this->currentToken.type) {
        case TokenType::LOCAL:
            return this->parseLocalStatement();
        case TokenType::RETURN:
            return this->parseReturnStatement();
        default:
            return nullptr;
        }
    }

    LocalStatement* Parser::parseLocalStatement()
    {
        auto* statement = new LocalStatement();
        statement->token = this->currentToken;

        if (!this->expectPeek(TokenType::IDENT)) {
            return nullptr;
        }

        statement->name = Identifier { this->currentToken, this->currentToken.literal };

        if (!this->expectPeek(TokenType::ASSIGN)) {
            return nullptr;
        }

        // while (this->currentTokenIsNot(TokenType::SEMICOLON)) {
        //     this->nextToken();
        // }

        return statement;
    }

    ReturnStatement* Parser::parseReturnStatement() const
    {
        auto* statement = new ReturnStatement();
        statement->token = this->currentToken;

        // while (this->currentTokenIsNot(TokenType::SEMICOLON)) {
        //     this->nextToken();
        // }

        return statement;
    }

    bool Parser::currentTokenIs(TokenType type) const
    {
        return this->currentToken.type == type;
    }

    bool Parser::currentTokenIsNot(TokenType type) const
    {
        return this->currentToken.type != type;
    }

    bool Parser::peekTokenIs(TokenType type) const
    {
        return this->peekToken.type == type;
    }

    bool Parser::peekTokenIsNot(TokenType type) const
    {
        return this->peekToken.type != type;
    }

    bool Parser::expectPeek(TokenType type)
    {
        if (this->peekTokenIs(type)) {
            this->nextToken();
            return true;
        }

        ParserError error = { };
        error.error = string_format(
            "'%s' expected near '%s' on line %i column %i",
            sTokenType[type], this->peekToken.literal.c_str(),
            this->peekToken.line, this->peekToken.col
        );
        error.line = this->peekToken.line;
        error.col = this->peekToken.col;
        this->errors.push_back(error);

        return false;
    }
} // namespace Aul
