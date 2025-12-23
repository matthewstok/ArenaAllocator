#include <iostream>
#include <vector>
#include <string>

#include "allocate.h"
#include "parser.h"
#include "tokenizer.h"

int main()
{
    std::string input = "let x = 3 + 4 * (2 - 1)";
    std::vector<Token> tokens = Token::tokenize(input);

    Arena arena(1024);

    Parser parser(tokens, arena);

    try 
    {
        AssignmentNode* root = parser.parseLetStatement();
        std::cout << "Parsed let statement: " << root->m_name << " = [AST node]" << '\n';
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Parsing error: " << e.what() << std::endl;
    }

    return 0;
}
