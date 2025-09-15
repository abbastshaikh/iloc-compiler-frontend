#pragma once

#include <Token.hpp>
#include <LinkedList.hpp>
#include <fstream>
#include <string>

class Scanner {
public:
    Scanner(const std::string filename);
    Token nextToken();

private:
    std::ifstream file;
};