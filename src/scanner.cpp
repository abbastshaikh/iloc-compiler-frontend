#include <Scanner.hpp>
#include <TransitionTable.hpp>
#include <fstream>

Scanner::Scanner(const std::string filename) {
    file = std::ifstream (filename);
    if (!file.is_open()){
        throw FileNotFoundException("Failed to open file: " + filename);
    }
    TransitionTable table;
}

Token Scanner::nextToken() {
    return Token(Category::CAT_EOF, -1);
}