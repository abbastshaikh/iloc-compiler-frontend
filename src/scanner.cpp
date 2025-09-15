#include <Scanner.hpp>
#include <Token.hpp>
#include <Opcode.hpp>
#include <LinkedList.hpp>
#include <iostream>
#include <fstream>

Scanner::Scanner(const std::string filename) {
    file = std::ifstream (filename);
    if (!file.is_open()){
        std::cerr << "ERROR: Failed to open file: " << filename << std::endl;
    }
}

Token Scanner::nextToken() {
    return Token(Category::CAT_EOF, -1);
}

// int c = 0;

// LinkedList<Token> tokenList;
// tokenList.append(Token(Category::CAT_ARITHOP, (int) Opcode::ADD));
// tokenList.append(Token(Category::CAT_REGISTER, 1));
// tokenList.append(Token(Category::CAT_COMMA, -1));
// tokenList.append(Token(Category::CAT_REGISTER, 2));
// // tokenList.append(Token(Category::CAT_INTO, -1));
// tokenList.append(Token(Category::CAT_REGISTER, 3));
// tokenList.append(Token(Category::CAT_EOL, -1));

// tokenList.append(Token(Category::CAT_ARITHOP, (int) Opcode::ADD));
// tokenList.append(Token(Category::CAT_REGISTER, 1));
// tokenList.append(Token(Category::CAT_COMMA, -1));
// tokenList.append(Token(Category::CAT_REGISTER, 2));
// tokenList.append(Token(Category::CAT_INTO, -1));
// tokenList.append(Token(Category::CAT_REGISTER, 3));
// tokenList.append(Token(Category::CAT_EOL, -1));

// tokenList.append(Token(Category::CAT_MEMOP, (int) Opcode::LOAD));
// tokenList.append(Token(Category::CAT_REGISTER, 1));
// tokenList.append(Token(Category::CAT_INTO, -1));
// // tokenList.append(Token(Category::CAT_REGISTER, 3));
// tokenList.append(Token(Category::CAT_EOL, -1));

// tokenList.append(Token(Category::CAT_EOL, -1));
// tokenList.append(Token(Category::CAT_EOL, -1));

// // tokenList.append(Token(Category::CAT_LOADI, (int) Opcode::LOADI));
// tokenList.append(Token(Category::CAT_CONSTANT, 12));
// tokenList.append(Token(Category::CAT_INTO, -1));
// tokenList.append(Token(Category::CAT_REGISTER, 3));
// tokenList.append(Token(Category::CAT_EOL, -1));

// tokenList.append(Token(Category::CAT_NOP, (int) Opcode::NOP));
// tokenList.append(Token(Category::CAT_EOL, -1));

// // tokenList.append(Token(Category::CAT_NOP, (int) Opcode::NOP));
// tokenList.append(Token(Category::CAT_EOL, -1));

// tokenList.append(Token(Category::CAT_EOF, -1));

// Node<Token>* current = tokenList.head;
// for (int i = 0; i < c; i ++) {
//     current = current -> next;
// }
// c++; 
// return current -> data;

// char ch;
// while(file.get(ch)){
//     std::cout << ch;
// }
// Token token (Category::CAT_NOP, (int) Opcode::NOP);
// return token;