#include "parser.h"


std::size_t Parser::currentTokenIndex() const { return m_token_index; }

void Parser::advanceTokenIndex()
{ 
    ++m_token_index;
}

bool Parser::match(TokenType t)
{
    if(t == m_tokenized[m_token_index].type)
    {
        advanceTokenIndex();
        return true;
    }
        return false;
}

void Parser::expect(TokenType t)
{
    if(t == m_tokenized[m_token_index].type)
    {
        advanceTokenIndex();
        return;
    }
        throw std::runtime_error("Expected X but found Y (EXAMPLE)");

}


ASTNode* Parser::parseExpression()
{
    ASTNode* left = parseTerm();

    while(m_tokenized[m_token_index].type == TokenType::BinaryOperator)
    {
        BinaryOp op = m_tokenized[m_token_index].op;
        advanceTokenIndex();

        ASTNode* right = parseTerm();

        if(op == BinaryOp::Add || op == BinaryOp::Sub)
        {
            left = allocate_in_arena<OperatorNode>(op, left, right);
        }
        else
        {
            --m_token_index;
            break;
        }
    }

    return left;

}

ASTNode* Parser::parsePrimary()
{
    Token current_token { m_tokenized[m_token_index] };

    if(current_token.type == TokenType::Number)
    {
        double value { std::stod(current_token.value) };

        NumberNode* node = allocate_in_arena<NumberNode>(value);
        advanceTokenIndex();

        return node;
    }
    else if(current_token.type == TokenType::Identifier)
    {
        IdentifierNode* node = allocate_in_arena<IdentifierNode>(current_token.value);

        advanceTokenIndex();

        return node;
    }
    else if(current_token.type == TokenType::OpenParen)
    {
        advanceTokenIndex();
        ASTNode* n = parseExpression();

        if(m_tokenized[m_token_index].type == TokenType::CloseParen)
        {
            advanceTokenIndex();
        }
        else
        {
            throw std::runtime_error("NO CLOSING PARENTHESES");
        }

        return n;
    }
    else
    {
        throw std::runtime_error("TOKEN IS NOT BIG THREE");
    }
}

ASTNode* Parser::parseTerm()
{
    ASTNode* left = parsePrimary();

    while(m_tokenized[m_token_index].type == TokenType::BinaryOperator)
    {
        BinaryOp op = m_tokenized[m_token_index].op;
        advanceTokenIndex();

        ASTNode* right = parsePrimary();

        if(op == BinaryOp::Multi || op == BinaryOp::Divid)
        {
            left = allocate_in_arena<OperatorNode>(op, left, right);
        }
        else
        {
            --m_token_index;
            break;
        }
    }
    return left;
}


AssignmentNode* Parser::parseLetStatement()
{
    expect(TokenType::Let);
    std::string var_name { m_tokenized[m_token_index].value };
    expect(TokenType::Identifier);
    expect(TokenType::Equals);

    ASTNode* expr = parseExpression();

    AssignmentNode* node = allocate_in_arena<AssignmentNode>(var_name, expr);
    return node;

}
