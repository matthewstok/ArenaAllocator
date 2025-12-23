#include <vector>
#include "tokenizer.h"

std::vector<Token> Token::tokenize(const std::string& sourceString)
{
    std::vector<Token> tokens;

    for (std::size_t i = 0; i < sourceString.length(); ++i)
    {
        char c = sourceString[i];

        if (c == ' ')
            continue;
        else if (std::isdigit(static_cast<unsigned char>(c)) || c == '.')
        {
            std::size_t start = i;
            while (i < sourceString.length() &&
                   (std::isdigit(static_cast<unsigned char>(sourceString[i])) || sourceString[i] == '.'))
            {
                ++i;
            }
            std::string number_string = sourceString.substr(start, i - start);
            tokens.push_back(Token{ number_string, TokenType::Number });
            --i;
        }

        else if (std::isalpha(static_cast<unsigned char>(c)) || c == '_')
        {
            std::size_t start = i;
            while (i < sourceString.length() &&
                   (std::isalnum(static_cast<unsigned char>(sourceString[i])) || sourceString[i] == '_'))
            {
                ++i;
            }
            std::string word_string = sourceString.substr(start, i - start);
            if(word_string == "let")
            {
                tokens.push_back(Token { word_string, TokenType::Let} );
            }
            else
            {
                tokens.push_back(Token{ word_string, TokenType::Identifier });
            }
            --i;
        }
        else
        {
            switch(c)
            {
                case '(': tokens.push_back(Token{ "(", TokenType::OpenParen }); break;
                case ')': tokens.push_back(Token{ ")", TokenType::CloseParen }); break;
                case '=': tokens.push_back(Token{ "=", TokenType::Equals }); break;
                case '+': tokens.push_back(Token{ "+", TokenType::BinaryOperator }); break;
                case '-': tokens.push_back(Token{ "-", TokenType::BinaryOperator }); break;
                case '*': tokens.push_back(Token{ "*", TokenType::BinaryOperator}); break;
                case '/': tokens.push_back(Token{ "/", TokenType::BinaryOperator }); break;
                default:
                    throw std::runtime_error(std::string("Unknown character: ") + c);
            }
        }
    }
    return tokens;
}
