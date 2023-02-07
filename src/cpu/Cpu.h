/**
 * @file Cpu.h
 * @brief CPU header
 * 
 * Write longer description here
 */

#include <cstdint>
#include <string>
#include <vector>

class System;

class Cpu
{
public:

    Cpu();
    ~Cpu();

    void clock();    //Main loop
    void ConnectSystem(System *s);
    
    //Registers

    uint16_t a = 0;  //Accumulator
    uint16_t d = 0;  //Direct Page
    uint16_t s = 0;  //Stack
    uint16_t pc = 0; //Program counter
    uint16_t x = 0;  //Index
    uint16_t y = 0;  //Index
    uint8_t db = 0;  //Data bank
    uint8_t pb = 0;  //Program bank

    enum FLAGS {
        C = (1 << 0),	// Carry Bit
		Z = (1 << 1),	// Zero
		I = (1 << 2),	// Disable IRQ Interrupts
		D = (1 << 3),	// Decimal Mode
		X = (1 << 4),	// Index register size (0=16-bit, 1=8-bit)
		M = (1 << 5),	// Accumulator register size (0=16-bit, 1=8-bit)
		V = (1 << 6),	// Overflow
		N = (1 << 7),	// Negative
    };

private:

    System *system = nullptr;
    uint8_t read(uint32_t addr);
    void    write(uint32_t addr, uint8_t data);

    uint8_t opcode = 0;
    uint8_t cycles = 0;
    uint16_t fetched = 0;   //Input value for ALU
    uint32_t addr_abs = 0;
    uint32_t addr_rel = 0;
    uint32_t temp = 0;
    
    struct Instruction {
        std::string name;
        uint8_t (Cpu::*operate)(void) = nullptr;
        uint8_t (Cpu::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
        uint8_t arguments = 0;
    };
    std::vector<Instruction> instructions;

    uint16_t fetch();

    //Flag Operations

    uint8_t GetFlag(FLAGS f);
    void    SetFlag(FLAGS f, bool v);
    
    //Addressing Modes

    uint8_t ABS(); //Absolute                            a
    uint8_t AII(); //Absolute Indexed Indirect           (a,x)
    uint8_t AIX(); //Absolute Indexed with X             a,x
    uint8_t AIY(); //Absolute Indexed with Y             a,y
    uint8_t ABI(); //Absolute Indirect                   (a)
    uint8_t ALX(); //Absolute Long Indexed with X        al,x
    uint8_t ABL(); //Absolute Long                       al
    uint8_t ACC(); //Accumulator                         A
    uint8_t BLK(); //Block Move                          xyc
    uint8_t DIN(); //Direct Indexed Indirect             (d,x)
    uint8_t DIX(); //Direct Indexed with X               d,x
    uint8_t DIY(); //Direct Indexed with y               d,y
    uint8_t DNI(); //Direct Indirect Indexed             (d),y
    uint8_t DLI(); //Direct Indirect Long Indexed        [d],Y
    uint8_t DNL(); //Direct Indirect Long                [d]
    uint8_t DRN(); //Direct Indirect                     (d)
    uint8_t DIR(); //Direct                              d
    uint8_t IMM(); //Immediate                           #
    uint8_t IMP(); //Implied                             i
    uint8_t PCL(); //Program Counter Relative Long       rl
    uint8_t PCR(); //Program Counter Relative            r
    uint8_t STK(); //Stack                               s
    uint8_t SKR(); //Stack Relative                      d,s
    uint8_t SNI(); //Stack Relative Indirect Indexed     (d,s),y


    //Opcodes
    uint8_t BRK();
    uint8_t BPL();
    uint8_t JSR();
    uint8_t BMI();
    uint8_t RTI();
    uint8_t BVC();
    uint8_t RTS();
    uint8_t BVS();
    uint8_t BRA();
    uint8_t BCC();
    uint8_t LDY();
    uint8_t BCS();
    uint8_t CPY();
    uint8_t BNE();
    uint8_t CPX();
    uint8_t BEQ();
    uint8_t ORA();
    uint8_t AND();
    uint8_t EOR();
    uint8_t ADC();
    uint8_t STA();
    uint8_t LDA();
    uint8_t CMP();
    uint8_t SBC();
    uint8_t COP();
    uint8_t WDM();
    uint8_t PER();
    uint8_t PRL();
    uint8_t BRL();
    uint8_t LDX();
    uint8_t REP();
    uint8_t SEP();
    uint8_t TSB();
    uint8_t TRB();
    uint8_t BIT();
    uint8_t MVP();
    uint8_t MVN();
    uint8_t STZ();
    uint8_t STY();
    uint8_t PEI();
    uint8_t PEA();
    uint8_t ASL();
    uint8_t ROL();
    uint8_t LSR();
    uint8_t ROR();
    uint8_t STX();
    uint8_t DEC();
    uint8_t INC();
    uint8_t PHP();
    uint8_t CLC();
    uint8_t PLP();
    uint8_t SEC();
    uint8_t PHA();
    uint8_t CLI();
    uint8_t PLA();
    uint8_t SEI();
    uint8_t DEY();
    uint8_t TYA();
    uint8_t TAY();
    uint8_t CLV();
    uint8_t INY();
    uint8_t CLD();
    uint8_t INX();
    uint8_t SED();
    uint8_t PHY();
    uint8_t PLY();
    uint8_t TXA();
    uint8_t TXS();
    uint8_t TAX();
    uint8_t TSX();
    uint8_t DEX();
    uint8_t PHX();
    uint8_t NOP();
    uint8_t PLX();
    uint8_t PHD();
    uint8_t TCS();
    uint8_t PLD();
    uint8_t TSC();
    uint8_t PHK();
    uint8_t TCD();
    uint8_t RTL();
    uint8_t TDC();
    uint8_t PHB();
    uint8_t TXY();
    uint8_t PLB();
    uint8_t TYX();
    uint8_t WAI();
    uint8_t STP();
    uint8_t XBA();
    uint8_t XCE();
    uint8_t JMP();
    uint8_t JML();


    uint8_t XXX();     //Default value for unimplemented opcodes
};