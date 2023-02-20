#include "Cpu.h"

namespace neslite
{
	Cpu::Cpu()
	{
    	instructions = 
		{
			{ "BRK", &Cpu::BRK, &Cpu::IMM, 7 },{ "ORA", &Cpu::ORA, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "ORA", &Cpu::ORA, &Cpu::ZP0, 3 },{ "ASL", &Cpu::ASL, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PHP", &Cpu::PHP, &Cpu::IMP, 3 },{ "ORA", &Cpu::ORA, &Cpu::IMM, 2 },{ "ASL", &Cpu::ASL, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ABS, 4 },{ "ASL", &Cpu::ASL, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BPL", &Cpu::BPL, &Cpu::REL, 2 },{ "ORA", &Cpu::ORA, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ZPX, 4 },{ "ASL", &Cpu::ASL, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "CLC", &Cpu::CLC, &Cpu::IMP, 2 },{ "ORA", &Cpu::ORA, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ABX, 4 },{ "ASL", &Cpu::ASL, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "JSR", &Cpu::JSR, &Cpu::ABS, 6 },{ "AND", &Cpu::AND, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "BIT", &Cpu::BIT, &Cpu::ZP0, 3 },{ "AND", &Cpu::AND, &Cpu::ZP0, 3 },{ "ROL", &Cpu::ROL, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PLP", &Cpu::PLP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::IMM, 2 },{ "ROL", &Cpu::ROL, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "BIT", &Cpu::BIT, &Cpu::ABS, 4 },{ "AND", &Cpu::AND, &Cpu::ABS, 4 },{ "ROL", &Cpu::ROL, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BMI", &Cpu::BMI, &Cpu::REL, 2 },{ "AND", &Cpu::AND, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::ZPX, 4 },{ "ROL", &Cpu::ROL, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "SEC", &Cpu::SEC, &Cpu::IMP, 2 },{ "AND", &Cpu::AND, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::ABX, 4 },{ "ROL", &Cpu::ROL, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "RTI", &Cpu::RTI, &Cpu::IMP, 6 },{ "EOR", &Cpu::EOR, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "EOR", &Cpu::EOR, &Cpu::ZP0, 3 },{ "LSR", &Cpu::LSR, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PHA", &Cpu::PHA, &Cpu::IMP, 3 },{ "EOR", &Cpu::EOR, &Cpu::IMM, 2 },{ "LSR", &Cpu::LSR, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "JMP", &Cpu::JMP, &Cpu::ABS, 3 },{ "EOR", &Cpu::EOR, &Cpu::ABS, 4 },{ "LSR", &Cpu::LSR, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BVC", &Cpu::BVC, &Cpu::REL, 2 },{ "EOR", &Cpu::EOR, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "EOR", &Cpu::EOR, &Cpu::ZPX, 4 },{ "LSR", &Cpu::LSR, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "CLI", &Cpu::CLI, &Cpu::IMP, 2 },{ "EOR", &Cpu::EOR, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "EOR", &Cpu::EOR, &Cpu::ABX, 4 },{ "LSR", &Cpu::LSR, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "RTS", &Cpu::RTS, &Cpu::IMP, 6 },{ "ADC", &Cpu::ADC, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "ADC", &Cpu::ADC, &Cpu::ZP0, 3 },{ "ROR", &Cpu::ROR, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PLA", &Cpu::PLA, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::IMM, 2 },{ "ROR", &Cpu::ROR, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "JMP", &Cpu::JMP, &Cpu::IND, 5 },{ "ADC", &Cpu::ADC, &Cpu::ABS, 4 },{ "ROR", &Cpu::ROR, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BVS", &Cpu::BVS, &Cpu::REL, 2 },{ "ADC", &Cpu::ADC, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::ZPX, 4 },{ "ROR", &Cpu::ROR, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "SEI", &Cpu::SEI, &Cpu::IMP, 2 },{ "ADC", &Cpu::ADC, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::ABX, 4 },{ "ROR", &Cpu::ROR, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "STA", &Cpu::STA, &Cpu::IZX, 6 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "STY", &Cpu::STY, &Cpu::ZP0, 3 },{ "STA", &Cpu::STA, &Cpu::ZP0, 3 },{ "STX", &Cpu::STX, &Cpu::ZP0, 3 },{ "???", &Cpu::XXX, &Cpu::IMP, 3 },{ "DEY", &Cpu::DEY, &Cpu::IMP, 2 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "TXA", &Cpu::TXA, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "STY", &Cpu::STY, &Cpu::ABS, 4 },{ "STA", &Cpu::STA, &Cpu::ABS, 4 },{ "STX", &Cpu::STX, &Cpu::ABS, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
			{ "BCC", &Cpu::BCC, &Cpu::REL, 2 },{ "STA", &Cpu::STA, &Cpu::IZY, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "STY", &Cpu::STY, &Cpu::ZPX, 4 },{ "STA", &Cpu::STA, &Cpu::ZPX, 4 },{ "STX", &Cpu::STX, &Cpu::ZPY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },{ "TYA", &Cpu::TYA, &Cpu::IMP, 2 },{ "STA", &Cpu::STA, &Cpu::ABY, 5 },{ "TXS", &Cpu::TXS, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "???", &Cpu::NOP, &Cpu::IMP, 5 },{ "STA", &Cpu::STA, &Cpu::ABX, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
			{ "LDY", &Cpu::LDY, &Cpu::IMM, 2 },{ "LDA", &Cpu::LDA, &Cpu::IZX, 6 },{ "LDX", &Cpu::LDX, &Cpu::IMM, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "LDY", &Cpu::LDY, &Cpu::ZP0, 3 },{ "LDA", &Cpu::LDA, &Cpu::ZP0, 3 },{ "LDX", &Cpu::LDX, &Cpu::ZP0, 3 },{ "???", &Cpu::XXX, &Cpu::IMP, 3 },{ "TAY", &Cpu::TAY, &Cpu::IMP, 2 },{ "LDA", &Cpu::LDA, &Cpu::IMM, 2 },{ "TAX", &Cpu::TAX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "LDY", &Cpu::LDY, &Cpu::ABS, 4 },{ "LDA", &Cpu::LDA, &Cpu::ABS, 4 },{ "LDX", &Cpu::LDX, &Cpu::ABS, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
			{ "BCS", &Cpu::BCS, &Cpu::REL, 2 },{ "LDA", &Cpu::LDA, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "LDY", &Cpu::LDY, &Cpu::ZPX, 4 },{ "LDA", &Cpu::LDA, &Cpu::ZPX, 4 },{ "LDX", &Cpu::LDX, &Cpu::ZPY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },{ "CLV", &Cpu::CLV, &Cpu::IMP, 2 },{ "LDA", &Cpu::LDA, &Cpu::ABY, 4 },{ "TSX", &Cpu::TSX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },{ "LDY", &Cpu::LDY, &Cpu::ABX, 4 },{ "LDA", &Cpu::LDA, &Cpu::ABX, 4 },{ "LDX", &Cpu::LDX, &Cpu::ABY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
			{ "CPY", &Cpu::CPY, &Cpu::IMM, 2 },{ "CMP", &Cpu::CMP, &Cpu::IZX, 6 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "CPY", &Cpu::CPY, &Cpu::ZP0, 3 },{ "CMP", &Cpu::CMP, &Cpu::ZP0, 3 },{ "DEC", &Cpu::DEC, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "INY", &Cpu::INY, &Cpu::IMP, 2 },{ "CMP", &Cpu::CMP, &Cpu::IMM, 2 },{ "DEX", &Cpu::DEX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "CPY", &Cpu::CPY, &Cpu::ABS, 4 },{ "CMP", &Cpu::CMP, &Cpu::ABS, 4 },{ "DEC", &Cpu::DEC, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BNE", &Cpu::BNE, &Cpu::REL, 2 },{ "CMP", &Cpu::CMP, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "CMP", &Cpu::CMP, &Cpu::ZPX, 4 },{ "DEC", &Cpu::DEC, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "CLD", &Cpu::CLD, &Cpu::IMP, 2 },{ "CMP", &Cpu::CMP, &Cpu::ABY, 4 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "CMP", &Cpu::CMP, &Cpu::ABX, 4 },{ "DEC", &Cpu::DEC, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "CPX", &Cpu::CPX, &Cpu::IMM, 2 },{ "SBC", &Cpu::SBC, &Cpu::IZX, 6 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "CPX", &Cpu::CPX, &Cpu::ZP0, 3 },{ "SBC", &Cpu::SBC, &Cpu::ZP0, 3 },{ "INC", &Cpu::INC, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "INX", &Cpu::INX, &Cpu::IMP, 2 },{ "SBC", &Cpu::SBC, &Cpu::IMM, 2 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::SBC, &Cpu::IMP, 2 },{ "CPX", &Cpu::CPX, &Cpu::ABS, 4 },{ "SBC", &Cpu::SBC, &Cpu::ABS, 4 },{ "INC", &Cpu::INC, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BEQ", &Cpu::BEQ, &Cpu::REL, 2 },{ "SBC", &Cpu::SBC, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "SBC", &Cpu::SBC, &Cpu::ZPX, 4 },{ "INC", &Cpu::INC, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "SED", &Cpu::SED, &Cpu::IMP, 2 },{ "SBC", &Cpu::SBC, &Cpu::ABY, 4 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "SBC", &Cpu::SBC, &Cpu::ABX, 4 },{ "INC", &Cpu::INC, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		};
	}

	Cpu::~Cpu() {};

	void Cpu::clock()
	{
		if (cycles == 0) {
			opcode = read(pc++);

			cycles = instructions[opcode].cycles;

			//Run address mode and operation functions
			//Returns any additional cycels we need to wait
			uint8_t addr_mode_add_cycles = (this->*instructions[opcode].addrmode)();
			uint8_t operation_add_cycles = (this->*instructions[opcode].operate)();

			cycles += addr_mode_add_cycles + operation_add_cycles;
		}

		cycles--;

	}

	uint8_t Cpu::GetFlag(FLAGS f)
	{
		return ((status & f) > 0) ? 1 : 0;
	}

	void Cpu::SetFlag(FLAGS f, bool v)
	{
		if (v) {
			status |= f;
		}
		else {
			status &= ~f;
		}
	}

	uint8_t Cpu::fetch()
	{
		if (instructions[opcode].addrmode != &Cpu::IMP) {
			fetched = read(addr);
		}
		return fetched;
	}

	// ADDRESSING MODES

	// Absolute
	uint8_t Cpu::ABS()
	{
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		addr = (hi << 8) | lo;
		return 0;
	}

	// Absolute indexed with X
	uint8_t Cpu::ABX()
	{
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		addr = ((hi << 8) | lo) + x;
		return 0;
	}

	// Absolute indexed with Y
	uint8_t Cpu::ABY()
	{
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		addr = ((hi << 8) | lo) + y;
		return 0;
	}

	// Immediate
	uint8_t Cpu::IMM()
	{
		addr = pc++;
		return 0;
	}

	// Implied
	uint8_t Cpu::IMP()
	{
		addr = a;
		return 0;
	}

	// Indirect
	uint8_t Cpu::IND()
	{
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		addr = read((hi << 8) | lo);
		return 0;
	}

	// Indirect indexed with X
	uint8_t Cpu::IZX()
	{
		addr = read(read(pc++)) + x;
		return 0;
	}

	// Indirect indexed with Y
	uint8_t Cpu::IZY()
	{
		addr = read(read(pc++)) + y;
		return 0;
	}

	//X indexed Indirect
	uint8_t Cpu::XIZ()
	{
		addr = read(read(pc++) + x);
		return 0;
	}

	//Y indexed Indirect
	uint8_t Cpu::YIZ()
	{
		addr = read(read(pc++) + y);
		return 0;
	}

	// Relative
	uint8_t Cpu::REL()
	{
		addr_rel = pc + read(pc++);
		return 0;
	}

	// Zero paged indexed
	uint8_t Cpu::ZP0()
	{
		addr = read(pc++);
		return 0;
	}

	// Zero page indexed with X
	uint8_t Cpu::ZPX()
	{
		addr = read(pc++) + x;
		return 0;
	}

	// Zero page indexed with Y
	uint8_t Cpu::ZPY()
	{
		addr = read(pc++) + y;
		return 0;
	}
	// ==============================
	// ========== OPCODES ==========
	// ==============================

	//Add with Carry
	uint8_t Cpu::ADC()
	{
		temp = (uint16_t) a + (uint16_t) fetch() + (uint16_t) GetFlag(C);
		SetFlag(C, temp & 0xff00);
		SetFlag(N, temp & 0x0080);
		SetFlag(V, (~((uint16_t) a ^ (uint16_t) fetched) 
			& ((uint16_t) a ^ (uint16_t) temp)) & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);
		a = temp & 0x00ff;
		return 0;
	}

	//Bitwise AND
	uint8_t Cpu::AND()
	{
		a = a & fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);

		return 0;
	}

	//Arithmetic Shift Left
	uint8_t Cpu::ASL()
	{
		fetch();
		
		temp = (uint16_t) fetched << 1;
		SetFlag(C, temp & 0xFF00);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, temp == 0x0000);

		if (instructions[opcode].addrmode == &Cpu::IMP) {
			a = temp & 0x00ff;
		}
		else {
			write(addr, temp & 0x00ff);
		}

		return 0;
	}

	//Test Bits
	uint8_t Cpu::BIT()
	{
		temp = a & fetch();
		SetFlag(V, (1 << 6));
		SetFlag(N, (1 << 7));
		SetFlag(Z, temp == 0x000);

		return 0;
	}

	//Break
	uint8_t Cpu::BRK()
	{
		pc++;
		return 0;
	}

	//Compare Accumulator
	uint8_t Cpu::CMP()
	{
		fetch();
		
		temp = (uint16_t)a - (uint16_t)fetched;

		SetFlag(C, a >= fetched);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Compare X Register
	uint8_t Cpu::CPX()
	{
		fetch();
		
		temp = (uint16_t)x - (uint16_t)fetched;

		SetFlag(C, x >= fetched);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Compare Y Register
	uint8_t Cpu::CPY()
	{
		fetch();
		
		temp = (uint16_t)y - (uint16_t)fetched;

		SetFlag(C, y >= fetched);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Decrement Memory
	uint8_t Cpu::DEC()
	{
		fetch();
		
		temp = fetched - 1;
		write(addr, temp & 0x00ff);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Bitwise XOR
	uint8_t Cpu::EOR()
	{
		a = a ^ fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);

		return 0;
	}

	//Increment Memory
	uint8_t Cpu::INC()
	{
		temp = fetch() + 1;
		write(addr, temp);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Jump
	uint8_t Cpu::JMP()
	{
		pc = addr;
		return 0;
	}

	//Jump to Subroutine
	uint8_t Cpu::JSR()
	{
		pc--;

		//Push current pc to stack then transfer control
		write(0x0100 + stack--, (pc >> 8) & 0x00ff);
		write(0x0100 + stack--, pc & 0x00ff);

		pc = addr;
		return 0;
	}

	//Load Accumulator
	uint8_t Cpu::LDA()
	{
		a = fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);
		return 0;
	}

	//Load X Register
	uint8_t Cpu::LDX()
	{
		x = fetch();
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Load Y Register
	uint8_t Cpu::LDY()
	{
		y = fetch();
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	//Logical Shift Right
	uint8_t Cpu::LSR()
	{
		fetch();

		SetFlag(C, fetched & 0x01);
		fetched = fetched >> 1;
		SetFlag(N, fetched & 0x80);
		SetFlag(Z, fetched == 0x00);
		return 0;
	}

	//No Operation
	uint8_t Cpu::NOP()
	{
		return 0;
	}

	//Bitwise OR
	uint8_t Cpu::ORA()
	{
		a = a | fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);
		return 0;
	}

	//Rotate Left
	uint8_t Cpu::ROL()
	{
		temp = (fetch() << 1) + GetFlag(C);
		SetFlag(C, temp & 0xff00);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		if (instructions[opcode].addrmode == &Cpu::IMP) {
			a = temp & 0x00ff;
		}
		else {
			write(addr, temp & 0x00ff);
		}

		return 0;
	}

	//Rotate Right
	uint8_t Cpu::ROR()
	{
		temp = fetch() << 7;
		if (GetFlag(C)) {
			temp = temp | 0x8000;
		}
		SetFlag(C, temp & 0x00ff);
		SetFlag(N, temp & 0x8000);
		SetFlag(Z, (temp & 0xff00) == 0x0000);

		temp = temp >> 8;

		if (instructions[opcode].addrmode == &Cpu::IMP) {
			a = temp & 0x00ff;
		}
		else {
			write(addr, temp & 0x00ff);
		}

		return 0;
	}

	//Return from Interrupt
	uint8_t Cpu::RTI()
	{
		status = read(0x0100 + stack++);
		pc = read(0x0100 + stack++);
		return 0;
	}

	//Return from Subroutine
	uint8_t Cpu::RTS()
	{
		uint8_t lo = read(0x0100 + stack++);
		uint8_t hi = read(0x0100 + stack++);
		pc = ((hi << 8) | lo) + 1;
		return 0;
	}

	//Subtract with Carry
	uint8_t Cpu::SBC()
	{
		uint16_t flip = ((uint16_t) fetch()) ^ 0x00ff;
		temp = (uint16_t) a + flip + (uint16_t) GetFlag(C);
		SetFlag(C, temp & 0xff00);
		SetFlag(N, temp & 0x0080);
		SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ flip) & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);
		a = temp & 0x00ff;
		return 0;
	}

	//Store Accumulator
	uint8_t Cpu::STA()
	{
		write(addr, a);
		return 0;
	}

	//Store X Register
	uint8_t Cpu::STX()
	{
		write(addr, x);
		return 0;
	}	
	//Store Y Register
	uint8_t Cpu::STY()
	{
		write(addr, y);
		return 0;
	}

	// ========================================
	// ========== BRANCH OPCODES ==========
	// ========================================

	//Branch on Plus
	uint8_t Cpu::BPL()
	{
		if (!GetFlag(N)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Minus
	uint8_t Cpu::BMI()
	{
		if (GetFlag(N)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Overflow Clear
	uint8_t Cpu::BVC()
	{
		if (!GetFlag(V)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Overflow Set
	uint8_t Cpu::BVS()
	{
		if (GetFlag(V)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Carry Clear
	uint8_t Cpu::BCC()
	{
		if (!GetFlag(C)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Carry Set
	uint8_t Cpu::BCS()
	{
		if (GetFlag(C)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Not Equal 
	uint8_t Cpu::BNE()
	{
		if (!GetFlag(Z)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	//Branch on Equal
	uint8_t Cpu::BPL()
	{
		if (GetFlag(Z)) {
			addr = pc + addr_rel;
			cycles += 1 + ((addr & 0xff00) != (pc & 0xff00));
			pc = addr;
		}

		cycles += 2;
		return 0;
	}

	// ========================================
	// ========== FLAG OPCODES ==========
	// ========================================

	//Clear Carry
	uint8_t Cpu::CLC()
	{
		SetFlag(C, false);
		return 0;
	}

	//Set Carry
	uint8_t Cpu::SEC()
	{
		SetFlag(C, true);
		return 0;
	}

	//Clear Interrupt
	uint8_t Cpu::CLI()
	{
		SetFlag(I, false);
		return 0;
	}

	//Set Interrupt
	uint8_t Cpu::SEI()
	{
		SetFlag(I, true);
		return 0;
	}

	//Clear Overflow
	uint8_t Cpu::CLV()
	{
		SetFlag(V, false);
		return 0;
	}

	//Set Overflow
	uint8_t Cpu::SEV()
	{
		SetFlag(V, true);
		return 0;
	}

	//Clear Decimal
	uint8_t Cpu::CLD()
	{
		SetFlag(D, false);
		return 0;
	}

	//Set Decimal
	uint8_t Cpu::SED()
	{
		SetFlag(D, true);
		return 0;
	}

	// ========================================
	// ========== REGISTER OPCODES ==========
	// ========================================

	//Transfer Accumulator to X
	uint8_t Cpu::TAX()
	{
		x = a;
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Transfer X to Accumulator
	uint8_t Cpu::TXA()
	{
		a = x;
		SetFlag(N, a & 0x80);
		SetFlag(N, a == 0x00);
		return 0;
	}

	//Decrement X
	uint8_t Cpu::DEX()
	{
		x--;
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Increment X
	uint8_t Cpu::INX()
	{
		x++;
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Transfer Accumulator to Y
	uint8_t Cpu::TAY()
	{
		x = a;
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	//Transfer Y to Accumulator
	uint8_t Cpu::TYA()
	{
		a = y;
		SetFlag(N, a & 0x80);
		SetFlag(N, a == 0x00);
		return 0;
	}

	//Decrement Y
	uint8_t Cpu::DEY()
	{
		x--;
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	//Increment Y
	uint8_t Cpu::INY()
	{
		x++;
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	// ========================================
	// ========== STACK OPCODES ==========
	// ========================================

	//Transfer X to stack
	uint8_t Cpu::TXS()
	{
		stack = x;
		return 0;
	}

	//Transfer stack to X
	uint8_t Cpu::TSX()
	{
		x = stack;
		return 0;
	}

	//Push Accumulator
	uint8_t Cpu::PHA()
	{
		write(0x0100 + stack--, a);
		return 0;
	}

	//Pop Accumulator
	uint8_t Cpu::PLA()
	{
		a = read(0x0100 + stack++);
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);
		return 0;
	}

	//Push Processor Status
	uint8_t Cpu::PHP()
	{
		write(0x0100 + stack--, status | B | U);
		SetFlag(B, 0);
		SetFlag(U, 0);
		return 0;
	}

	//Pull Processor Status
	uint8_t Cpu::PLP()
	{
		status = read(0x0100 + stack++);
		SetFlag(U, 1);
		return 0;
	}

	//Invalid Opcode
	uint8_t Cpu::XXX()
	{
		return 0;
	}
}

