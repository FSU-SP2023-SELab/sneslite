#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace sneslite
{
    class Bus;

    class Cpu
    {
        public:

            Cpu();
            ~Cpu();

            void ConnectBus(Bus *n) { bus = n; }

            /// @brief Accumulator
            std::uint8_t a = 0;
            /// @brief X index register
            std::uint8_t x = 0;
            /// @brief Y index register
            std::uint8_t y = 0;
            /// @brief Stack pointer register
            std::uint8_t stack = 0;
            /// @brief Status register
            std::uint8_t status = 0;
            /// @brief Program Counter register
            std::uint16_t pc = 0;

            enum FLAGS {
                C = (1 << 0),
                Z = (1 << 1),
                I = (1 << 2),
                D = (1 << 3),
                B = (1 << 4),
                U = (1 << 5),
                V = (1 << 6),
                N = (1 << 7)
            };

            /// @brief Takes 8 cycles, resets all registers, sets pc to value at 0xfffc lo 0xfffd hi
            void reset();
            /// @brief Takes 7 cycles, if I = 0 pushes pc then status to stack and sets pc to 0xfffe lo 0xffff hi
            void irq();
            /// @brief Takes 8 cycles, pushes pc then status to stack and sets pc to 0xfffa lo 0xfffb hi
            void nmi();
            /// @brief Perform one clock cycle
            void clock();

        private:

            Bus* bus = nullptr;

	        /// @brief Reads byte of memory at specific location
	        /// @param a 16-bit address in memory
	        /// @return Byte at address a
	        std::uint8_t read(std::uint16_t a);

	        /// @brief Writes byte to memory at specific location
	        /// @param a 16-bit address in memory
	        /// @param d Byte to be written
	        void write(std::uint16_t a, std::uint8_t d);

            std::uint8_t opcode = 0;
            std::uint8_t cycles = 0;
            std::uint8_t fetched = 0;
            std::uint16_t addr = 0;
            std::uint16_t addr_rel = 0;
            std::uint16_t temp = 0;

            /// @brief Contains information to execute instruction
            struct Instruction {
                std::string name;
                std::uint8_t (Cpu::*operate)(void) = nullptr;
                std::uint8_t (Cpu::*addrmode)(void) = nullptr;
                std::uint8_t cycles = 0;
            };
            /// @brief Index with opcode to obtain its instruction information
            std::vector<Instruction> instructions;

            /// @brief Fetches the data located at addr in memory
            /// @return Byte at address addr in memory
            std::uint8_t fetch();

            std::uint8_t GetFlag(FLAGS f);
            void SetFlag(FLAGS f, bool v);

            /// @brief Pushes byte to stack, rooted at 0x0100 in memory
            /// @param d Byte to be pushed
            void PushStack(std::uint8_t d);

            /// @brief Pops byte off of stack, rooted at 0x0100 in memory
            /// @return Byte popped off
            std::uint8_t PopStack();

            //ADDRESSING MODES

            /// @brief Absolute
            /// @return 0 extra cycles
            std::uint8_t ABS(); 

            /// @brief Absolute Indexed with X
            /// @return TODO 1 extra if new page
            std::uint8_t ABX();

            /// @brief Absolute Indexed with Y
            /// @return TODO 1 extra if new page
            std::uint8_t ABY();
            
            /// @brief Immediate
            /// @return 0 extra cycles
            std::uint8_t IMM();
            
            /// @brief Implied
            /// @return 0 extra cycles
            std::uint8_t IMP();

            /// @brief Indirect
            /// @return TODO extra cycles if branch
            std::uint8_t IND();

            /// @brief Indirect Indexed with X
            /// @return TODO extra cycles if branch
            std::uint8_t IZX();

            /// @brief Indirect Indexed with Y
            /// @return TODO extra cycles if branch
            std::uint8_t IZY();

            /// @brief X Indexed Indirect :: ($LL, X) :: X added to address
            /// @return TODO 1 extra if new page
            std::uint8_t XIZ();

            /// @brief Y Indexed Indirect :: ($LL, Y) :: Y added to address
            /// @return TODO 1 extra if new page
            std::uint8_t YIZ();

            /// @brief Relative TODO
            /// @return 0 extra cycles
            std::uint8_t REL();

            /// @brief Zero Page Indexed
            /// @return 0 extra cycles
            std::uint8_t ZP0();

            /// @brief Zero Page Indexed with X
            /// @return 0 extra cycles
            std::uint8_t ZPX();

            /// @brief Zero Page Indexed with Y
            /// @return 0 extra cycles
            std::uint8_t ZPY();

            //OPCODES

            std::uint8_t ADC();  //Add with carry
            std::uint8_t AND();  //Bitwise and
            std::uint8_t ASL();  //Arithmetic shift left
            std::uint8_t BIT();  //Test bits
            std::uint8_t BRK();  //Break
            std::uint8_t CMP();  //Compare Accumulator
            std::uint8_t CPX();  //Compare X register
            std::uint8_t CPY();  //Compare Y register
            std::uint8_t DEC();  //Decrement memory
            std::uint8_t EOR();  //Bitwise xor
            std::uint8_t INC();  //Increment memory
            std::uint8_t JMP();  //Jump
            std::uint8_t JSR();  //Jump to subroutine
            std::uint8_t LDA();  //Load accumulator
            std::uint8_t LDX();  //Load X register
            std::uint8_t LDY();  //Load Y register
            std::uint8_t LSR();  //Logical shift right
            std::uint8_t NOP();  //No operation
            std::uint8_t ORA();  //Bitwise or
            std::uint8_t ROL();  //Rotate left
            std::uint8_t ROR();  //Rotate right
            std::uint8_t RTI();  //Return from interrupt
            std::uint8_t RTS();  //Return from subroutine
            std::uint8_t SBC();  //Subtract with carry
            std::uint8_t STA();  //Store accumulator
            std::uint8_t STX();  //Store X register
            std::uint8_t STY();  //Store Y register

            //BRANCH OPCODES
            std::uint8_t BPL();  //Branch on plus
            std::uint8_t BMI();  //Branch on minus
            std::uint8_t BVC();  //Branch on overflow clear
            std::uint8_t BVS();  //Branch on overflow set
            std::uint8_t BCC();  //Branch on carry clear
            std::uint8_t BCS();  //Branch on carry set
            std::uint8_t BNE();  //Branch on not equal
            std::uint8_t BEQ();  //Branch on equal

            //FLAG OPCODES

            std::uint8_t CLC();  //Clear carry
            std::uint8_t SEC();  //Set carry
            std::uint8_t CLI();  //Clear interrupt
            std::uint8_t SEI();  //Set interrupt
            std::uint8_t CLV();  //Clear overflow
            std::uint8_t SEV();  //Set overflow
            std::uint8_t CLD();  //Clear decimal
            std::uint8_t SED();  //Set decimal

            //REGISTER OPCODES
            std::uint8_t TAX();  //Transfer a to x
            std::uint8_t TXA();  //Transfer x to a
            std::uint8_t DEX();  //Decrement x
            std::uint8_t INX();  //Increment X
            std::uint8_t TAY();  //Transfer a to y
            std::uint8_t TYA();  //Transfer y to a
            std::uint8_t DEY();  //Decrement y
            std::uint8_t INY();  //Increment y

            //STACK INSTRUCTIONS
            std::uint8_t TXS();  //Transfer x to stk ptr
            std::uint8_t TSX();  //Transfer stk ptr to x
            std::uint8_t PHA();  //Push accumulator
            std::uint8_t PLA();  //Pull accumulator
            std::uint8_t PHP();  //Push processor status
            std::uint8_t PLP();  //Pull processor status

            std::uint8_t XXX();  //No opcode
    };
}