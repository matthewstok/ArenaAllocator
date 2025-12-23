#ifndef MY_PARSER_H
#define MY_PARSER_H

#include <iostream>
#include "tokenizer.h"
#include "allocate.h"

enum class ASTNodeType
{
    Number,
    Identifier,
    Binary,
    Assignment,
};

struct ASTNode
{
    ASTNodeType type;
};

struct NumberNode : ASTNode
{
    double m_value;

    NumberNode(double value)
    : m_value { value }
    {
        type = ASTNodeType::Number;
    }
};

struct IdentifierNode : ASTNode
{
    std::string m_name;

    IdentifierNode(std::string name)
    : m_name { std::move(name) }
    {
        type = ASTNodeType::Identifier;
    }
};

struct OperatorNode : ASTNode
{
    BinaryOp m_op;
    ASTNode* m_left;
    ASTNode* m_right;

    OperatorNode(BinaryOp op, ASTNode* left, ASTNode* right)
    : m_op { op }, m_left { left }, m_right { right }
    {
        type = ASTNodeType::Binary;
    }
};

struct AssignmentNode : ASTNode
{
    std::string m_name;
    ASTNode* m_expression;

    AssignmentNode(std::string name, ASTNode* expression)
    : m_name { std::move(name) }, m_expression { expression }
    {
        type = ASTNodeType::Assignment;
    }
};

class Parser
{
    private:
        std::vector<Token>& m_tokenized;
        std::size_t m_token_index;
        Arena& m_arena;

    public:
        Parser(std::vector<Token>& tokenized, Arena& arena)
        : m_tokenized { tokenized }, m_token_index { 0 }, m_arena { arena }
        { }


        std::size_t currentTokenIndex() const;
        void advanceTokenIndex();

        bool match(TokenType t);
        void expect(TokenType t);

        ASTNode* parseExpression();

        ASTNode* parseTerm();
        ASTNode* parsePrimary();
        AssignmentNode* parseLetStatement();

        template<typename T, typename... Args>
        T* allocate_in_arena(Args&&... args)
        {
            char* mem = m_arena.allocate(sizeof(T), alignof(T));
            return new(mem) T(std::forward<Args>(args)...);
        }

};

#endif //MY_PARSER_H