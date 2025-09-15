#include <Scanner.hpp>
#include <Token.hpp>
#include <Opcode.hpp>
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