#include <Scanner.hpp>
#include <TransitionTable.hpp>
#include <stack>
#include <fstream>
#include <iostream>

Scanner::Scanner(const std::string filename) {
    file = std::ifstream (filename);
    if (!file.is_open()){
        throw FileNotFoundException("Failed to open file: " + filename);
    }
    TransitionTable table;
    index = 0;
    line = 0;
    eof = false;
    this->readLine();
}

Token Scanner::nextToken() {

    int currState;
    int nextState;
    char currChar;
    char nextChar;

    if (eof) {
        return Token(Category::CAT_EOF, -1); 
    }

    currChar = buffer[index];
    currState = table.table[0][currChar];

    // if (currState == 37) {
    //     readLine();
    //     return Token(Category::CAT_EOL, -1);
    // }

    index ++;
    nextChar = buffer[index];
    nextState = table.table[currState][nextChar];

    while (nextState != -1) {
        index ++;
        currChar = nextChar;
        currState = nextState;
        nextChar = buffer[index];
        nextState = table.table[currState][nextChar];
    }

    if (table.accepting.find(currState) != table.accepting.end()) {
        Category category = table.stateToCategory[currState];
        if (category == Category::CAT_EOL) {
            readLine();
        }
        return Token(category, 0);
        
    } else {
        index = buffer.size() - 1;
        return Token(Category::CAT_INVAL, -1);
    }

}

void Scanner::readLine() {
    if (file.eof()) {
        eof = true;
        return;
    }
    std::getline(file, buffer);
    buffer += "\n";
    index = 0;
    line ++;
}