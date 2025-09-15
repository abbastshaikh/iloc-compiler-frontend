#pragma once

#include <Opcode.hpp>

struct Operand {
    int SR = 0;
    int VR = 0;
    int PR = 0;
    int NU = 0;
};

struct Operation {
    int line;
    Opcode opcode;
    Operand op1;
    Operand op2;
    Operand op3;

    std::string toString () {
        switch (this->opcode) {
            case Opcode::LOAD: 
            case Opcode::STORE: 
                return OpcodeNames[(int) opcode] + " [ sr" + std::to_string(op1.SR) + " ]," + " [ ]," + " [ sr" + std::to_string(op3.SR) + " ]";
            case Opcode::LOADI:
                return OpcodeNames[(int) opcode] + " [ val " + std::to_string(op1.SR) + " ]," + " [ ]," + " [ sr" + std::to_string(op3.SR) + " ]";
            case Opcode::ADD: 
            case Opcode::SUB:
            case Opcode::MULT: 
            case Opcode::LSHIFT: 
            case Opcode::RSHIFT: 
                return OpcodeNames[(int) opcode] + " [ sr" + std::to_string(op1.SR) + " ]," + " [ sr" + std::to_string(op2.SR) + " ]," + " [ sr" + std::to_string(op3.SR) + " ]";
            case Opcode::OUTPUT:
                return OpcodeNames[(int) opcode] + " [ val " + std::to_string(op1.SR) + " ]," + " [ ]," + " [ ]";
            case Opcode::NOP: 
                return OpcodeNames[(int) opcode] + " [ ]," + " [ ]," + " [ ]";
            default:
                throw std::invalid_argument("Operaiton has invalid opcode.");
        }
    }
};

