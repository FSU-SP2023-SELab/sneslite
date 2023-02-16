#include <cstdint>
#include <vector>
#include <string>

class System;

class Cpu
{
public:

    Cpu();
    ~Cpu();

    void clock();
    void ConnectSystem(System *s);

    uint8_t a = 0;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t s = 0;
    uint8_t pc = 0;

    enum FLAGS {
        C = (1 << 0),
        Z = (2 << 0),
        I = (3 << 0),
        D = (4 << 0),
        V = (5 << 0),
        N = (6 << 0)
    };

private:

    System *system = nullptr;
    uint8_t read(uint8_t addr);
    void write(uint8_t addr, uint8_t data);

    uint8_t opcode = 0;
    uint8_t cycles = 0;
    uint8_t fetched = 0;
    uint16_t addr_abs = 0;
    uint16_t addr_rel = 0;
    uint8_t temp = 0;

    struct Instruction {
        std::string name;
        uint8_t (Cpu::*operate)(void) = nullptr;
        uint8_t (Cpu::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
        uint8_t arguments = 0;
    };
    std::vector<Instruction> instructions;

    uint8_t fetch();

    uint8_t GetFlag(FLAGS f);
    void SetFlag(FLAGS f, bool v);

    //ADDRESSING MODES

    uint8_t ABS();  //Absolute
    uint8_t ABX();  //Absolute X indexed
    uint8_t ABY();  //Absolute Y indexed
    uint8_t IMM();  //Immediate
    uint8_t IMP();  //Implied
    uint8_t IND();  //Indirect
    uint8_t IZX();  //Indirect X indexed
    uint8_t IZY();  //Indirect Y indexed
    uint8_t REL();  //Relative
    uint8_t ZP0();  //Zero Page
    uint8_t ZPX();  //Zero Page X indexed
    uint8_t ZPY();  //Zero Page Y indexed

    //OPCODES

    uint8_t ADC();  //Add with carry
    uint8_t AND();  //Bitwise and
    uint8_t ASL();  //Arithmetic shift left
    uint8_t BIT();  //Test bits
    uint8_t BRK();  //Break
    uint8_t CMP();  //Compare Accumulator
    uint8_t CPX();  //Compare X register
    uint8_t CPY();  //Compare Y register
    uint8_t DEC();  //Decrement memory
    uint8_t EOR();  //Bitwise xor
    uint8_t INC();  //Increment memory
    uint8_t JMP();  //Jump
    uint8_t JSR();  //Jump to subroutine
    uint8_t LDA();  //Load accumulator
    uint8_t LDX();  //Load X register
    uint8_t LDY();  //Load Y register
    uint8_t LSR();  //Logical shift right
    uint8_t NOP();  //No operation
    uint8_t ORA();  //Bitwise or
    uint8_t ROL();  //Rotate left
    uint8_t ROR();  //Rotate right
    uint8_t RTI();  //Return from interrupt
    uint8_t RTS();  //Return from subroutine
    uint8_t SBC();  //Subtract with carry
    uint8_t STA();  //Store accumulator
    uint8_t STX();  //Store X register
    uint8_t STY();  //Store Y register

    //BRANCH OPCODES
    uint8_t BPL();  //Branch on plus
    uint8_t BMI();  //Branch on minus
    uint8_t BVC();  //Branch on overflow clear
    uint8_t BVS();  //Branch on overflow set
    uint8_t BCC();  //Branch on carry clear
    uint8_t BCS();  //Branch on carry set
    uint8_t BNE();  //Branch on not equal
    uint8_t BEQ();  //Branch on equal

    //FLAG OPCODES

    uint8_t CLC();  //Clear carry
    uint8_t SEC();  //Set carry
    uint8_t CLI();  //Clear interrupt
    uint8_t SEI();  //Set interrupt
    uint8_t CLV();  //Clear overflow
    uint8_t CLD();  //Clear decimal
    uint8_t SED();  //Set overflow

    //REGISTER INSTRUCTIONS
    uint8_t TAX();  //Transfer a to x
    uint8_t TXA();  //Transfer x to a
    uint8_t DEX();  //Decrement x
    uint8_t INX();  //Increment X
    uint8_t TAY();  //Transfer a to y
    uint8_t TYA();  //Transfer y to a
    uint8_t DEY();  //Decrement y
    uint8_t INY();  //Increment y

    //STACK INSTRUCTIONS
    uint8_t TXS();  //Transfer x to stk ptr
    uint8_t TSX();  //Transfer stk ptr to x
    uint8_t PHA();  //Push accumulator
    uint8_t PLA();  //Pull accumulator
    uint8_t PHP();  //Push processor status
    uint8_t PLP();  //Pull processor status

    uint8_t XXX();  //No opcode
};