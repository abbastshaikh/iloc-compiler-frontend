#include <Parser.hpp>
#include <Scanner.hpp>
#include <Operation.hpp>
#include <exception>

InternalRepresentation Parser::parse() {
    LinkedList<Operation> representation;
    bool error = false;
    int count = 0;

    Token token = scanner.nextToken();    
    while (token.category != Category::CAT_EOF) {
        this->line++;
        switch (token.category) {
            case Category::CAT_MEMOP:
                try {
                    representation.append(this->finishMEMOP(static_cast<Opcode>(token.lexeme)));
                    count++;
                } catch (const InvalidTokenException& e) {
                    error = true;
                    std::cerr << "ERROR (" << this->line << "): "  << e.what() << std::endl;
                    if (e.getToken().category == Category::CAT_EOF) {
                        throw new UnexpectedEOFException("Unexpected EOF at line " + std::to_string(this->line));
                    }
                }    
                break;
            case Category::CAT_LOADI:
                try {
                    representation.append(finishLOADI(static_cast<Opcode>(token.lexeme)));
                    count++;
                } catch (const InvalidTokenException& e) {
                    error = true;
                    std::cerr << "ERROR (" << this->line << "): "  << e.what() << std::endl;
                    if (e.getToken().category == Category::CAT_EOF) {
                        throw new UnexpectedEOFException("Unexpected EOF at line " + std::to_string(this->line));
                    }
                }  
                break;
            case Category::CAT_ARITHOP:
                try {
                    representation.append(finishARITHOP(static_cast<Opcode>(token.lexeme)));
                    count++;
                } catch (const InvalidTokenException& e) {
                    error = true;
                    std::cerr << "ERROR (" << this->line << "): "  << e.what() << std::endl;
                    if (e.getToken().category == Category::CAT_EOF) {
                        throw new UnexpectedEOFException("Unexpected EOF at line " + std::to_string(this->line));
                    }
                }  
                break;
            case Category::CAT_OUTPUT:
                try {
                    representation.append(finishOUTPUT(static_cast<Opcode>(token.lexeme)));
                    count++;
                } catch (const InvalidTokenException& e) {
                    error = true;
                    std::cerr << "ERROR (" << this->line << "): "  << e.what() << std::endl;
                    if (e.getToken().category == Category::CAT_EOF) {
                        throw new UnexpectedEOFException("Unexpected EOF at line " + std::to_string(this->line));
                    }
                }  
                break;
            case Category::CAT_NOP:
                try {
                    representation.append(finishNOP(static_cast<Opcode>(token.lexeme)));
                    count++;
                } catch (const InvalidTokenException& e) {
                    error = true;
                    std::cerr << "ERROR (" << this->line << "): "  << e.what() << std::endl;
                    if (e.getToken().category == Category::CAT_EOF) {
                        throw new UnexpectedEOFException("Unexpected EOF at line " + std::to_string(this->line));
                    }
                }  
                break;
            case Category::CAT_EOL:
                break;
            default:
                error = true;
                std::cerr << "ERROR (" << this->line << "): Unexpected token: " << token.getLexeme() << std::endl;
                this->readToNextLine();
        }

        // TODO: Handle did not reach EOF, i.e. next token fails without reaching EOF
        token = scanner.nextToken();
    }

    if (error) {
        throw new ParseFailedException("");
    }
    return {count, &representation};
}

Operation Parser::finishMEMOP(Opcode opcode) {
    
    Operation op;
    op.line = this->line;
    op.opcode = opcode;

    Token token = scanner.nextToken();
    if (token.category != Category::CAT_REGISTER) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected register, got " + token.getLexeme());
    }
    op.op1.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_INTO) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected \"=>\", got " + token.getLexeme());
    }

    token = scanner.nextToken();
    if (token.category != Category::CAT_REGISTER) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected register, got " + token.getLexeme());
    }
    op.op3.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_EOL) {
        if (token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected EOL, got " + token.getLexeme());
    }

    return op;
}

Operation Parser::finishLOADI(Opcode opcode) {
    
    Operation op;
    op.line = this->line;
    op.opcode = opcode;

    Token token = scanner.nextToken();
    if (token.category != Category::CAT_CONSTANT) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected constant, got " + token.getLexeme());
    }
    op.op1.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_INTO) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected \"=>\", got " + token.getLexeme());
    }

    token = scanner.nextToken();
    if (token.category != Category::CAT_REGISTER) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected register, got " + token.getLexeme());
    }
    op.op3.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_EOL) {
        if (token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected EOL, got " + token.getLexeme());
    }

    return op;
}

Operation Parser::finishARITHOP(Opcode opcode) {
    
    Operation op;
    op.line = this->line;
    op.opcode = opcode;

    Token token = scanner.nextToken();
    if (token.category != Category::CAT_REGISTER) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected register, got " + token.getLexeme());
    }
    op.op1.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_COMMA) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected \",\", got " + token.getLexeme());
    }

    token = scanner.nextToken();
    if (token.category != Category::CAT_REGISTER) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected register, got " + token.getLexeme());
    }
    op.op2.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_INTO) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected =>, got " + token.getLexeme());
    }

    token = scanner.nextToken();
    if (token.category != Category::CAT_REGISTER) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected register, got " + token.getLexeme());
    }
    op.op3.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_EOL) {
        if (token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected EOL, got " + token.getLexeme());
    }

    return op;
}

Operation Parser::finishOUTPUT(Opcode opcode) {
    
    Operation op;
    op.line = this->line;
    op.opcode = opcode;

    Token token = scanner.nextToken();
    if (token.category != Category::CAT_CONSTANT) {
        if (token.category != Category::CAT_EOL && token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected constant, got " + token.getLexeme());
    }
    op.op1.SR = token.lexeme;

    token = scanner.nextToken();
    if (token.category != Category::CAT_EOL) {
        if (token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected EOL, got " + token.getLexeme());
    }

    return op;
}

Operation Parser::finishNOP(Opcode opcode) {
    Operation op;
    op.line = this->line;
    op.opcode = opcode;

    Token token = scanner.nextToken();
    if (token.category != Category::CAT_EOL) {
        if (token.category != Category::CAT_EOF) {
            this->readToNextLine();
        }
        throw InvalidTokenException(token, "Expected EOL, got " + token.getLexeme());
    }

    return op;
}

void Parser::readToNextLine () {
    Token token = scanner.nextToken();
    while (token.category != Category::CAT_EOL) {
        if (token.category == Category::CAT_EOF) {
            throw new UnexpectedEOFException("Unexpected EOF at line " + std::to_string(this->line));
        }
        token = scanner.nextToken();
    }
}
