#ifndef MY_TOKENIZER_H
#define MY_TOKENIZER_H

#include <string>

//forward decalre
enum class BinaryOp { Add, Sub, Multi, Divid, None };

enum TokenType
{
    Number,
    Identifier,
    Equals,
    OpenParen,
    CloseParen,
    BinaryOperator,
    Let,
};

struct Token
{
    std::string value;
    TokenType type;
    BinaryOp op = BinaryOp::None;
    
    static std::vector<Token> tokenize(const std::string& sourceString);
};

#endif //MY_TOKENIZER_H
