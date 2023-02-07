/**
 * @file Cpu.cpp
 * @brief CPU definitions
 */

#include "Cpu.h"
#include "System.h"


Cpu::Cpu()
{
    instructions = {
        //0                                     1                                     2                                     3                                     4                                     5                                     6                                     7                                     8                                     9                                     A                                     B                                     C                                     D                                     E                                     F 
/*0*/	{ "BRK", &Cpu::BRK, &Cpu::STK, 7, 2 },{ "ORA", &Cpu::ORA, &Cpu::DIN, 6, 2 },{ "COP", &Cpu::COP, &Cpu::STK, 7, 2 },{ "ORA", &Cpu::ORA, &Cpu::SKR, 4, 2 },{ "TSB", &Cpu::TSB, &Cpu::DIR, 5, 2 },{ "ORA", &Cpu::ORA, &Cpu::DIR, 3, 2 },{ "ASL", &Cpu::ASL, &Cpu::DIR, 5, 2 },{ "ORA", &Cpu::ORA, &Cpu::DNL, 6, 2 },{ "PHP", &Cpu::PHP, &Cpu::STK, 3, 1 },{ "ORA", &Cpu::ORA, &Cpu::IMM, 2, 2 },{ "ASL", &Cpu::ASL, &Cpu::ACC, 2, 1 },{ "PHD", &Cpu::PHD, &Cpu::STK, 4, 1 },{ "TSB", &Cpu::TSB, &Cpu::ABS, 6, 3 },{ "ORA", &Cpu::ORA, &Cpu::ABS, 4, 3 },{ "ASL", &Cpu::ASL, &Cpu::ABS, 6, 3 },{ "ORA", &Cpu::ORA, &Cpu::ABL, 5, 4 },
/*1*/	{ "BPL", &Cpu::BPL, &Cpu::PCR, 2, 2 },{ "ORA", &Cpu::ORA, &Cpu::DNI, 5, 2 },{ "ORA", &Cpu::ORA, &Cpu::DRN, 5, 2 },{ "ORA", &Cpu::ORA, &Cpu::SNI, 7, 2 },{ "TRB", &Cpu::TRB, &Cpu::DIR, 5, 2 },{ "ORA", &Cpu::ORA, &Cpu::DIX, 4, 2 },{ "ASL", &Cpu::ASL, &Cpu::DIX, 6, 2 },{ "ORA", &Cpu::ORA, &Cpu::DLI, 6, 2 },{ "CLC", &Cpu::CLC, &Cpu::IMP, 2, 1 },{ "ORA", &Cpu::ORA, &Cpu::AIY, 4, 3 },{ "INC", &Cpu::INC, &Cpu::ACC, 2, 1 },{ "TCS", &Cpu::TCS, &Cpu::IMP, 2, 1 },{ "TRB", &Cpu::TRB, &Cpu::ABS, 6, 3 },{ "ORA", &Cpu::ORA, &Cpu::AIX, 4, 3 },{ "ASL", &Cpu::ASL, &Cpu::AIX, 7, 3 },{ "ORA", &Cpu::ORA, &Cpu::ALX, 5, 4 },
/*2*/	{ "JSR", &Cpu::JSR, &Cpu::ABS, 6, 3 },{ "AND", &Cpu::AND, &Cpu::DIN, 6, 2 },{ "JSR", &Cpu::JSR, &Cpu::ABL, 8, 4 },{ "AND", &Cpu::AND, &Cpu::SKR, 4, 2 },{ "BIT", &Cpu::BIT, &Cpu::DIR, 3, 2 },{ "AND", &Cpu::AND, &Cpu::DIR, 3, 2 },{ "ROL", &Cpu::ROL, &Cpu::DIR, 5, 2 },{ "AND", &Cpu::AND, &Cpu::DNL, 6, 2 },{ "PLP", &Cpu::PLP, &Cpu::STK, 4, 1 },{ "AND", &Cpu::AND, &Cpu::IMM, 2, 2 },{ "ROL", &Cpu::ROL, &Cpu::ACC, 2, 1 },{ "PLD", &Cpu::PLD, &Cpu::STK, 5, 1 },{ "BIT", &Cpu::BIT, &Cpu::ABS, 4, 3 },{ "AND", &Cpu::AND, &Cpu::ABS, 4, 3 },{ "ROL", &Cpu::ROL, &Cpu::ABS, 6, 3 },{ "AND", &Cpu::AND, &Cpu::ABL, 5, 4 },
/*3*/	{ "BMI", &Cpu::BMI, &Cpu::PCR, 2, 2 },{ "AND", &Cpu::AND, &Cpu::DNI, 5, 2 },{ "AND", &Cpu::AND, &Cpu::DRN, 5, 2 },{ "AND", &Cpu::AND, &Cpu::SNI, 7, 2 },{ "BIT", &Cpu::BIT, &Cpu::DIX, 4, 2 },{ "AND", &Cpu::AND, &Cpu::DIX, 4, 2 },{ "ROL", &Cpu::ROL, &Cpu::DIX, 6, 2 },{ "AND", &Cpu::AND, &Cpu::DLI, 6, 2 },{ "SEC", &Cpu::SEC, &Cpu::IMP, 2, 1 },{ "AND", &Cpu::AND, &Cpu::AIY, 4, 3 },{ "DEC", &Cpu::DEC, &Cpu::ACC, 2, 1 },{ "TSC", &Cpu::TSC, &Cpu::IMP, 2, 1 },{ "BIT", &Cpu::BIT, &Cpu::AIX, 4, 3 },{ "AND", &Cpu::AND, &Cpu::AIX, 4, 3 },{ "ROL", &Cpu::ROL, &Cpu::AIX, 7, 3 },{ "AND", &Cpu::AND, &Cpu::ALX, 5, 4 },
/*4*/	{ "RTI", &Cpu::RTI, &Cpu::STK, 7, 1 },{ "EOR", &Cpu::EOR, &Cpu::DIN, 6, 2 },{ "WDM", &Cpu::WDM, &Cpu::IMP, 2, 2 },{ "EOR", &Cpu::EOR, &Cpu::SKR, 4, 2 },{ "MVP", &Cpu::MVP, &Cpu::BLK, 7, 3 },{ "EOR", &Cpu::EOR, &Cpu::DIR, 3, 2 },{ "LSR", &Cpu::LSR, &Cpu::DIR, 5, 2 },{ "EOR", &Cpu::EOR, &Cpu::DNL, 6, 2 },{ "PHA", &Cpu::PHA, &Cpu::STK, 3, 1 },{ "EOR", &Cpu::EOR, &Cpu::IMM, 2, 2 },{ "LSR", &Cpu::LSR, &Cpu::ACC, 2, 1 },{ "PHK", &Cpu::PHK, &Cpu::STK, 3, 1 },{ "JMP", &Cpu::JMP, &Cpu::ABS, 3, 3 },{ "EOR", &Cpu::EOR, &Cpu::ABS, 4, 3 },{ "LSR", &Cpu::LSR, &Cpu::ABS, 6, 3 },{ "EOR", &Cpu::EOR, &Cpu::ABL, 5, 4 },
/*5*/	{ "BVC", &Cpu::BVC, &Cpu::PCR, 2, 2 },{ "EOR", &Cpu::EOR, &Cpu::DNI, 5, 2 },{ "EOR", &Cpu::EOR, &Cpu::DRN, 5, 2 },{ "EOR", &Cpu::EOR, &Cpu::SNI, 7, 2 },{ "MVN", &Cpu::MVN, &Cpu::BLK, 7, 3 },{ "EOR", &Cpu::EOR, &Cpu::DIX, 4, 2 },{ "LSR", &Cpu::LSR, &Cpu::DIX, 6, 2 },{ "EOR", &Cpu::EOR, &Cpu::DLI, 6, 2 },{ "CLI", &Cpu::CLI, &Cpu::IMP, 2, 1 },{ "EOR", &Cpu::EOR, &Cpu::AIY, 4, 3 },{ "PHY", &Cpu::PHY, &Cpu::STK, 3, 1 },{ "TCD", &Cpu::TCD, &Cpu::IMP, 2, 1 },{ "JMP", &Cpu::JMP, &Cpu::ABL, 4, 4 },{ "EOR", &Cpu::EOR, &Cpu::AIX, 4, 3 },{ "LSR", &Cpu::LSR, &Cpu::AIX, 7, 3 },{ "EOR", &Cpu::EOR, &Cpu::ALX, 5, 4 },
/*6*/	{ "RTS", &Cpu::RTS, &Cpu::STK, 6, 1 },{ "ADC", &Cpu::ADC, &Cpu::DIN, 6, 2 },{ "PER", &Cpu::PER, &Cpu::STK, 6, 3 },{ "ADC", &Cpu::ADC, &Cpu::SKR, 4, 2 },{ "STZ", &Cpu::STZ, &Cpu::DIR, 3, 2 },{ "ADC", &Cpu::ADC, &Cpu::DIR, 3, 2 },{ "ROR", &Cpu::ROR, &Cpu::DIR, 5, 2 },{ "EOR", &Cpu::EOR, &Cpu::DNL, 6, 2 },{ "PLA", &Cpu::PLA, &Cpu::STK, 4, 1 },{ "ADC", &Cpu::ADC, &Cpu::IMM, 2, 2 },{ "ROR", &Cpu::ROR, &Cpu::ACC, 2, 1 },{ "RTL", &Cpu::RTL, &Cpu::STK, 6, 1 },{ "JMP", &Cpu::JMP, &Cpu::ABI, 5, 3 },{ "ADC", &Cpu::ADC, &Cpu::ABS, 4, 3 },{ "ROR", &Cpu::ROR, &Cpu::ABS, 6, 3 },{ "ADC", &Cpu::ADC, &Cpu::ABL, 5, 4 },
/*7*/	{ "BVS", &Cpu::BVS, &Cpu::PCR, 2, 2 },{ "ADC", &Cpu::ADC, &Cpu::DNI, 5, 2 },{ "ADC", &Cpu::ADC, &Cpu::DRN, 5, 2 },{ "ADC", &Cpu::ADC, &Cpu::SNI, 7, 2 },{ "STZ", &Cpu::STZ, &Cpu::DIX, 4, 2 },{ "ADC", &Cpu::ADC, &Cpu::DIX, 4, 2 },{ "ROR", &Cpu::ROR, &Cpu::DIX, 6, 2 },{ "ADC", &Cpu::ADC, &Cpu::DLI, 6, 2 },{ "SEI", &Cpu::SEI, &Cpu::IMP, 2, 1 },{ "ADC", &Cpu::ADC, &Cpu::AIY, 4, 3 },{ "PLY", &Cpu::PLY, &Cpu::STK, 4, 1 },{ "TDC", &Cpu::TDC, &Cpu::IMP, 2, 1 },{ "JMP", &Cpu::JMP, &Cpu::AII, 6, 3 },{ "ADC", &Cpu::ADC, &Cpu::AIX, 4, 3 },{ "ROR", &Cpu::ROR, &Cpu::AIX, 7, 3 },{ "ADC", &Cpu::ADC, &Cpu::ALX, 5, 4 },
/*8*/	{ "BRA", &Cpu::BRA, &Cpu::PCR, 2, 2 },{ "STA", &Cpu::STA, &Cpu::DIN, 6, 2 },{ "BRL", &Cpu::BRL, &Cpu::PCL, 4, 3 },{ "STA", &Cpu::STA, &Cpu::SKR, 4, 2 },{ "STY", &Cpu::STY, &Cpu::DIR, 3, 2 },{ "STA", &Cpu::STA, &Cpu::DIR, 3, 2 },{ "STX", &Cpu::STX, &Cpu::DIR, 3, 2 },{ "ADC", &Cpu::ADC, &Cpu::DNL, 6, 2 },{ "DEY", &Cpu::DEY, &Cpu::IMP, 2, 1 },{ "BIT", &Cpu::BIT, &Cpu::IMP, 2, 2 },{ "TXA", &Cpu::TXA, &Cpu::IMP, 2, 1 },{ "PHB", &Cpu::PHB, &Cpu::STK, 3, 1 },{ "STY", &Cpu::STY, &Cpu::ABS, 4, 3 },{ "STA", &Cpu::STA, &Cpu::ABS, 4, 3 },{ "STX", &Cpu::STX, &Cpu::ABS, 4, 3 },{ "STA", &Cpu::STA, &Cpu::ABL, 5, 4 },
/*9*/	{ "BCC", &Cpu::BCC, &Cpu::PCR, 2, 2 },{ "STA", &Cpu::STA, &Cpu::DNI, 6, 2 },{ "STA", &Cpu::STA, &Cpu::DRN, 5, 2 },{ "STA", &Cpu::STA, &Cpu::SNI, 7, 2 },{ "STY", &Cpu::STY, &Cpu::DIX, 4, 2 },{ "STA", &Cpu::STA, &Cpu::DIX, 4, 2 },{ "STX", &Cpu::STX, &Cpu::DIY, 4, 2 },{ "STA", &Cpu::STA, &Cpu::DLI, 2, 2 },{ "TYA", &Cpu::TYA, &Cpu::IMP, 2, 1 },{ "STA", &Cpu::STA, &Cpu::AIY, 5, 3 },{ "TXS", &Cpu::TXS, &Cpu::IMP, 2, 1 },{ "TXY", &Cpu::TXY, &Cpu::IMP, 2, 1 },{ "STZ", &Cpu::STZ, &Cpu::ABS, 4, 3 },{ "STA", &Cpu::STA, &Cpu::AIX, 5, 3 },{ "STZ", &Cpu::STZ, &Cpu::AIX, 5, 3 },{ "STA", &Cpu::STA, &Cpu::ALX, 5, 4 },
/*A*/	{ "LDY", &Cpu::LDY, &Cpu::IMM, 2, 2 },{ "LDA", &Cpu::LDA, &Cpu::DIN, 6, 2 },{ "LDX", &Cpu::LDX, &Cpu::IMM, 2, 2 },{ "STA", &Cpu::STA, &Cpu::SKR, 4, 2 },{ "LDY", &Cpu::LDY, &Cpu::DIR, 3, 2 },{ "LDA", &Cpu::LDA, &Cpu::DIR, 3, 2 },{ "LDX", &Cpu::LDX, &Cpu::DIR, 3, 2 },{ "STA", &Cpu::STA, &Cpu::DNL, 6, 2 },{ "TAY", &Cpu::TAY, &Cpu::IMP, 2, 1 },{ "LDA", &Cpu::LDA, &Cpu::IMM, 2, 2 },{ "TAX", &Cpu::TAX, &Cpu::IMP, 2, 1 },{ "PLB", &Cpu::PLB, &Cpu::STK, 4, 1 },{ "LDY", &Cpu::LDY, &Cpu::ABS, 4, 3 },{ "LDA", &Cpu::LDA, &Cpu::ABS, 4, 3 },{ "LDX", &Cpu::LDX, &Cpu::ABS, 4, 3 },{ "LDA", &Cpu::LDA, &Cpu::ABL, 5, 4 },
/*B*/	{ "BCS", &Cpu::BCS, &Cpu::PCR, 2, 2 },{ "LDA", &Cpu::LDA, &Cpu::DNI, 5, 2 },{ "LDA", &Cpu::LDA, &Cpu::DRN, 5, 2 },{ "LDA", &Cpu::LDA, &Cpu::SNI, 7, 2 },{ "LDY", &Cpu::LDY, &Cpu::DIX, 4, 2 },{ "LDA", &Cpu::LDA, &Cpu::DIX, 4, 2 },{ "LDX", &Cpu::LDX, &Cpu::DIY, 4, 2 },{ "LDA", &Cpu::LDA, &Cpu::DLI, 6, 2 },{ "CLV", &Cpu::CLV, &Cpu::IMP, 2, 1 },{ "LDA", &Cpu::LDA, &Cpu::AIY, 4, 3 },{ "TSX", &Cpu::TSX, &Cpu::IMP, 2, 1 },{ "TYX", &Cpu::TYX, &Cpu::IMP, 4, 1 },{ "LDY", &Cpu::LDY, &Cpu::AIX, 4, 3 },{ "LDA", &Cpu::LDA, &Cpu::AIX, 4, 3 },{ "LDX", &Cpu::LDX, &Cpu::AIY, 4, 3 },{ "LDA", &Cpu::LDA, &Cpu::ALX, 5, 4 },
/*C*/	{ "CPY", &Cpu::CPY, &Cpu::IMM, 2, 2 },{ "CMP", &Cpu::CMP, &Cpu::DIN, 6, 2 },{ "REP", &Cpu::REP, &Cpu::IMM, 3, 2 },{ "LDA", &Cpu::LDA, &Cpu::SKR, 4, 2 },{ "CPY", &Cpu::CPY, &Cpu::DIR, 3, 2 },{ "CMP", &Cpu::CMP, &Cpu::DIR, 3, 2 },{ "DEC", &Cpu::DEC, &Cpu::DIR, 5, 2 },{ "LDA", &Cpu::LDA, &Cpu::DNL, 6, 2 },{ "INY", &Cpu::INY, &Cpu::IMP, 2, 1 },{ "CMP", &Cpu::CMP, &Cpu::IMM, 2, 2 },{ "DEX", &Cpu::DEX, &Cpu::IMP, 2, 1 },{ "WAI", &Cpu::WAI, &Cpu::IMP, 2, 1 },{ "CPY", &Cpu::CPY, &Cpu::ABS, 4, 3 },{ "CMP", &Cpu::CMP, &Cpu::ABS, 4, 3 },{ "DEC", &Cpu::DEC, &Cpu::ABS, 6, 3 },{ "CMP", &Cpu::CMP, &Cpu::ABL, 5, 4 },
/*D*/	{ "BNE", &Cpu::BNE, &Cpu::PCR, 2, 2 },{ "CMP", &Cpu::CMP, &Cpu::DNI, 5, 2 },{ "CMP", &Cpu::CMP, &Cpu::DRN, 7, 2 },{ "CMP", &Cpu::CMP, &Cpu::SNI, 7, 2 },{ "PEI", &Cpu::PEI, &Cpu::STK, 6, 2 },{ "CMP", &Cpu::CMP, &Cpu::DIX, 4, 2 },{ "DEC", &Cpu::DEC, &Cpu::DIX, 6, 2 },{ "CMP", &Cpu::CMP, &Cpu::DLI, 6, 2 },{ "CLD", &Cpu::CLD, &Cpu::IMP, 2, 1 },{ "CMP", &Cpu::CMP, &Cpu::AIY, 4, 3 },{ "PHX", &Cpu::PHX, &Cpu::STK, 3, 1 },{ "STP", &Cpu::STP, &Cpu::IMP, 3, 1 },{ "JML", &Cpu::JML, &Cpu::ABI, 6, 3 },{ "CMP", &Cpu::CMP, &Cpu::AIX, 4, 3 },{ "DEC", &Cpu::DEC, &Cpu::AIX, 7, 3 },{ "CMP", &Cpu::CMP, &Cpu::ALX, 5, 4 },
/*E*/	{ "CPX", &Cpu::CPX, &Cpu::IMM, 2, 2 },{ "SBC", &Cpu::SBC, &Cpu::DIN, 6, 2 },{ "SEP", &Cpu::SEP, &Cpu::IMM, 4, 2 },{ "SBC", &Cpu::SBC, &Cpu::SKR, 4, 2 },{ "CPX", &Cpu::CPX, &Cpu::DIR, 3, 2 },{ "SBC", &Cpu::SBC, &Cpu::DIR, 3, 2 },{ "INC", &Cpu::INC, &Cpu::DIR, 5, 2 },{ "CMP", &Cpu::CMP, &Cpu::DNL, 6, 2 },{ "INX", &Cpu::INX, &Cpu::IMP, 2, 1 },{ "SBC", &Cpu::SBC, &Cpu::IMM, 2, 2 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2, 1 },{ "XBA", &Cpu::XBA, &Cpu::IMP, 3, 1 },{ "CPX", &Cpu::CPX, &Cpu::ABS, 4, 3 },{ "SBC", &Cpu::SBC, &Cpu::ABS, 4, 3 },{ "INC", &Cpu::INC, &Cpu::ABS, 6, 3 },{ "SBC", &Cpu::SBC, &Cpu::ABL, 5, 4 },
/*F*/	{ "BEQ", &Cpu::BEQ, &Cpu::PCR, 2, 2 },{ "SBC", &Cpu::SBC, &Cpu::DNI, 5, 2 },{ "SBC", &Cpu::SBC, &Cpu::DRN, 7, 2 },{ "SBC", &Cpu::SBC, &Cpu::SNI, 7, 2 },{ "PEA", &Cpu::PEA, &Cpu::STK, 5, 3 },{ "SBC", &Cpu::SBC, &Cpu::DIX, 4, 2 },{ "INC", &Cpu::INC, &Cpu::DIX, 6, 2 },{ "SBC", &Cpu::SBC, &Cpu::DLI, 6, 2 },{ "SED", &Cpu::SED, &Cpu::IMP, 2, 1 },{ "SBC", &Cpu::SBC, &Cpu::AIY, 4, 3 },{ "PLX", &Cpu::PLX, &Cpu::STK, 4, 1 },{ "XCE", &Cpu::XCE, &Cpu::IMP, 2, 1 },{ "JSR", &Cpu::JSR, &Cpu::AII, 8, 3 },{ "SBC", &Cpu::SBC, &Cpu::AIX, 4, 3 },{ "INC", &Cpu::INC, &Cpu::AIX, 7, 3 },{ "SBC", &Cpu::SBC, &Cpu::ALX, 5, 4 },
	};
}

Cpu::~Cpu() {}

void Cpu::clock()
{
    if (cycles == 0) {
        opcode = read(pc);
        pc++;

        cycles = instructions[opcode].cycles;

        //Run address mode and operation functions
        //Returns any additional cycles we need to wait
        uint8_t addr_mode_additional_cycles = (this->*instructions[opcode].addrmode)();
        uint8_t operation_additional_cycles = (this->*instructions[opcode].operate)();

        //getExceptions() - a function that will adjust cycles based on FLAGS

        cycles += addr_mode_additional_cycles + operation_additional_cycles;
    }

    cycles--;
}

void Cpu::ConnectSystem(System *s)
{
    system = s;
}

uint8_t Cpu::read(uint32_t addr)
{
    return system->read_ram(addr);
}

void Cpu::write(uint32_t addr, uint8_t data)
{
    system->write_ram(addr, data);
}

//=========================================
//==============ADDRESS MODES==============
//=========================================

//Absolute
uint8_t Cpu::ABS()
{
    uint8_t lo = pc++;
    uint8_t hi = pc++;
    addr_abs = (db << 16) & (hi << 8) & lo;
    return 0;
}

//Absolute indexed with X
uint8_t Cpu::AIX()
{
    ABS();
    addr_abs += x;
    return 0;
}

//Absolute indexed with Y
uint8_t Cpu::AIX()
{
    ABS();
    addr_abs += y;
    return 0;
}

//Absolute long
uint8_t Cpu::ABL()
{
    uint8_t lo = pc++;
    uint8_t mid = pc++;
    uint8_t hi = pc++;
    addr_abs = (hi << 16) & (mid << 8) & lo;
    return 0;
}

//Address Mode Implied
uint8_t Cpu::IMP()
{
    addr_abs = a;
    return 0;
}

//Address Mode Immediate
uint8_t Cpu::IMM()
{
    if (GetFlag(M)) {
        addr_abs = pc++;
        return 0;
    }

    addr_abs = ((pc+1 << 8) & pc+2);
    pc += 2;
    return 0;
}

//Opcode And
uint8_t Cpu::AND()
{
    a = a & addr_abs;
    return 0;
}