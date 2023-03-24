#include "Cpu.h"
#include "Bus.h"

namespace sneslite
{
	Cpu::Cpu()
	{
    	instructions = 
		{
			{ "BRK", &Cpu::BRK, &Cpu::IMM, 7 }, { "ORA", &Cpu::ORA, &Cpu::IZX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 3 }, { "ORA", &Cpu::ORA, &Cpu::ZP0, 3 },
			{ "ASL", &Cpu::ASL, &Cpu::ZP0, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 }, { "PHP", &Cpu::PHP, &Cpu::IMP, 3 },
			{ "ORA", &Cpu::ORA, &Cpu::IMM, 2 }, { "ASL", &Cpu::ASL, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "ORA", &Cpu::ORA, &Cpu::ABS, 4 }, { "ASL", &Cpu::ASL, &Cpu::ABS, 6 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "BPL", &Cpu::BPL, &Cpu::REL, 2 }, { "ORA", &Cpu::ORA, &Cpu::IZY, 5 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 },
			{ "ORA", &Cpu::ORA, &Cpu::ZPX, 4 }, { "ASL", &Cpu::ASL, &Cpu::ZPX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "CLC", &Cpu::CLC, &Cpu::IMP, 2 }, { "ORA", &Cpu::ORA, &Cpu::ABY, 4 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "ORA", &Cpu::ORA, &Cpu::ABX, 4 },
			{ "ASL", &Cpu::ASL, &Cpu::ABX, 7 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "JSR", &Cpu::JSR, &Cpu::ABS, 6 },
			{ "AND", &Cpu::AND, &Cpu::IZX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 },
			{ "BIT", &Cpu::BIT, &Cpu::ZP0, 3 }, { "AND", &Cpu::AND, &Cpu::ZP0, 3 }, { "ROL", &Cpu::ROL, &Cpu::ZP0, 5 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 5 }, { "PLP", &Cpu::PLP, &Cpu::IMP, 4 }, { "AND", &Cpu::AND, &Cpu::IMM, 2 },
			{ "ROL", &Cpu::ROL, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "BIT", &Cpu::BIT, &Cpu::ABS, 4 },
			{ "AND", &Cpu::AND, &Cpu::ABS, 4 }, { "ROL", &Cpu::ROL, &Cpu::ABS, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BMI", &Cpu::BMI, &Cpu::REL, 2 }, { "AND", &Cpu::AND, &Cpu::IZY, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "AND", &Cpu::AND, &Cpu::ZPX, 4 },
			{ "ROL", &Cpu::ROL, &Cpu::ZPX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "SEC", &Cpu::SEC, &Cpu::IMP, 2 },
			{ "AND", &Cpu::AND, &Cpu::ABY, 4 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "AND", &Cpu::AND, &Cpu::ABX, 4 }, { "ROL", &Cpu::ROL, &Cpu::ABX, 7 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "RTI", &Cpu::RTI, &Cpu::IMP, 6 }, { "EOR", &Cpu::EOR, &Cpu::IZX, 6 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 3 },
			{ "EOR", &Cpu::EOR, &Cpu::ZP0, 3 }, { "LSR", &Cpu::LSR, &Cpu::ZP0, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 },
			{ "PHA", &Cpu::PHA, &Cpu::IMP, 3 }, { "EOR", &Cpu::EOR, &Cpu::IMM, 2 }, { "LSR", &Cpu::LSR, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "JMP", &Cpu::JMP, &Cpu::ABS, 3 }, { "EOR", &Cpu::EOR, &Cpu::ABS, 4 },
			{ "LSR", &Cpu::LSR, &Cpu::ABS, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "BVC", &Cpu::BVC, &Cpu::REL, 2 },
			{ "EOR", &Cpu::EOR, &Cpu::IZY, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "EOR", &Cpu::EOR, &Cpu::ZPX, 4 }, { "LSR", &Cpu::LSR, &Cpu::ZPX, 6 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "CLI", &Cpu::CLI, &Cpu::IMP, 2 }, { "EOR", &Cpu::EOR, &Cpu::ABY, 4 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 },
			{ "EOR", &Cpu::EOR, &Cpu::ABX, 4 }, { "LSR", &Cpu::LSR, &Cpu::ABX, 7 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "RTS", &Cpu::RTS, &Cpu::IMP, 6 }, { "ADC", &Cpu::ADC, &Cpu::IZX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 3 }, { "ADC", &Cpu::ADC, &Cpu::ZP0, 3 },
			{ "ROR", &Cpu::ROR, &Cpu::ZP0, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 }, { "PLA", &Cpu::PLA, &Cpu::IMP, 4 },
			{ "ADC", &Cpu::ADC, &Cpu::IMM, 2 }, { "ROR", &Cpu::ROR, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "JMP", &Cpu::JMP, &Cpu::IND, 5 }, { "ADC", &Cpu::ADC, &Cpu::ABS, 4 }, { "ROR", &Cpu::ROR, &Cpu::ABS, 6 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "BVS", &Cpu::BVS, &Cpu::REL, 2 }, { "ADC", &Cpu::ADC, &Cpu::IZY, 5 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 },
			{ "ADC", &Cpu::ADC, &Cpu::ZPX, 4 }, { "ROR", &Cpu::ROR, &Cpu::ZPX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "SEI", &Cpu::SEI, &Cpu::IMP, 2 }, { "ADC", &Cpu::ADC, &Cpu::ABY, 4 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "ADC", &Cpu::ADC, &Cpu::ABX, 4 },
			{ "ROR", &Cpu::ROR, &Cpu::ABX, 7 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 },
			{ "STA", &Cpu::STA, &Cpu::IZX, 6 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "STY", &Cpu::STY, &Cpu::ZP0, 3 }, { "STA", &Cpu::STA, &Cpu::ZP0, 3 }, { "STX", &Cpu::STX, &Cpu::ZP0, 3 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 3 }, { "DEY", &Cpu::DEY, &Cpu::IMP, 2 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 },
			{ "TXA", &Cpu::TXA, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "STY", &Cpu::STY, &Cpu::ABS, 4 },
			{ "STA", &Cpu::STA, &Cpu::ABS, 4 }, { "STX", &Cpu::STX, &Cpu::ABS, 4 }, { "???", &Cpu::XXX, &Cpu::IMP, 4 },
			{ "BCC", &Cpu::BCC, &Cpu::REL, 2 }, { "STA", &Cpu::STA, &Cpu::IZY, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "STY", &Cpu::STY, &Cpu::ZPX, 4 }, { "STA", &Cpu::STA, &Cpu::ZPX, 4 },
			{ "STX", &Cpu::STX, &Cpu::ZPY, 4 }, { "???", &Cpu::XXX, &Cpu::IMP, 4 }, { "TYA", &Cpu::TYA, &Cpu::IMP, 2 },
			{ "STA", &Cpu::STA, &Cpu::ABY, 5 }, { "TXS", &Cpu::TXS, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 5 }, { "STA", &Cpu::STA, &Cpu::ABX, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 5 }, { "LDY", &Cpu::LDY, &Cpu::IMM, 2 }, { "LDA", &Cpu::LDA, &Cpu::IZX, 6 },
			{ "LDX", &Cpu::LDX, &Cpu::IMM, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "LDY", &Cpu::LDY, &Cpu::ZP0, 3 },
			{ "LDA", &Cpu::LDA, &Cpu::ZP0, 3 }, { "LDX", &Cpu::LDX, &Cpu::ZP0, 3 }, { "???", &Cpu::XXX, &Cpu::IMP, 3 },
			{ "TAY", &Cpu::TAY, &Cpu::IMP, 2 }, { "LDA", &Cpu::LDA, &Cpu::IMM, 2 }, { "TAX", &Cpu::TAX, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "LDY", &Cpu::LDY, &Cpu::ABS, 4 }, { "LDA", &Cpu::LDA, &Cpu::ABS, 4 },
			{ "LDX", &Cpu::LDX, &Cpu::ABS, 4 }, { "???", &Cpu::XXX, &Cpu::IMP, 4 }, { "BCS", &Cpu::BCS, &Cpu::REL, 2 },
			{ "LDA", &Cpu::LDA, &Cpu::IZY, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 },
			{ "LDY", &Cpu::LDY, &Cpu::ZPX, 4 }, { "LDA", &Cpu::LDA, &Cpu::ZPX, 4 }, { "LDX", &Cpu::LDX, &Cpu::ZPY, 4 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 4 }, { "CLV", &Cpu::CLV, &Cpu::IMP, 2 }, { "LDA", &Cpu::LDA, &Cpu::ABY, 4 },
			{ "TSX", &Cpu::TSX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 4 }, { "LDY", &Cpu::LDY, &Cpu::ABX, 4 },
			{ "LDA", &Cpu::LDA, &Cpu::ABX, 4 }, { "LDX", &Cpu::LDX, &Cpu::ABY, 4 }, { "???", &Cpu::XXX, &Cpu::IMP, 4 },
			{ "CPY", &Cpu::CPY, &Cpu::IMM, 2 }, { "CMP", &Cpu::CMP, &Cpu::IZX, 6 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "CPY", &Cpu::CPY, &Cpu::ZP0, 3 }, { "CMP", &Cpu::CMP, &Cpu::ZP0, 3 },
			{ "DEC", &Cpu::DEC, &Cpu::ZP0, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 5 }, { "INY", &Cpu::INY, &Cpu::IMP, 2 },
			{ "CMP", &Cpu::CMP, &Cpu::IMM, 2 }, { "DEX", &Cpu::DEX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "CPY", &Cpu::CPY, &Cpu::ABS, 4 }, { "CMP", &Cpu::CMP, &Cpu::ABS, 4 }, { "DEC", &Cpu::DEC, &Cpu::ABS, 6 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "BNE", &Cpu::BNE, &Cpu::REL, 2 }, { "CMP", &Cpu::CMP, &Cpu::IZY, 5 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 },
			{ "CMP", &Cpu::CMP, &Cpu::ZPX, 4 }, { "DEC", &Cpu::DEC, &Cpu::ZPX, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "CLD", &Cpu::CLD, &Cpu::IMP, 2 }, { "CMP", &Cpu::CMP, &Cpu::ABY, 4 }, { "NOP", &Cpu::NOP, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "CMP", &Cpu::CMP, &Cpu::ABX, 4 },
			{ "DEC", &Cpu::DEC, &Cpu::ABX, 7 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 }, { "CPX", &Cpu::CPX, &Cpu::IMM, 2 },
			{ "SBC", &Cpu::SBC, &Cpu::IZX, 6 }, { "???", &Cpu::NOP, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 8 },
			{ "CPX", &Cpu::CPX, &Cpu::ZP0, 3 }, { "SBC", &Cpu::SBC, &Cpu::ZP0, 3 }, { "INC", &Cpu::INC, &Cpu::ZP0, 5 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 5 }, { "INX", &Cpu::INX, &Cpu::IMP, 2 }, { "SBC", &Cpu::SBC, &Cpu::IMM, 2 },
			{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 }, { "???", &Cpu::SBC, &Cpu::IMP, 2 }, { "CPX", &Cpu::CPX, &Cpu::ABS, 4 },
			{ "SBC", &Cpu::SBC, &Cpu::ABS, 4 }, { "INC", &Cpu::INC, &Cpu::ABS, 6 }, { "???", &Cpu::XXX, &Cpu::IMP, 6 },
			{ "BEQ", &Cpu::BEQ, &Cpu::REL, 2 }, { "SBC", &Cpu::SBC, &Cpu::IZY, 5 }, { "???", &Cpu::XXX, &Cpu::IMP, 2 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 8 },	{ "???", &Cpu::NOP, &Cpu::IMP, 4 }, { "SBC", &Cpu::SBC, &Cpu::ZPX, 4 },
			{ "INC", &Cpu::INC, &Cpu::ZPX, 6 },	{ "???", &Cpu::XXX, &Cpu::IMP, 6 }, { "SED", &Cpu::SED, &Cpu::IMP, 2 },
			{ "SBC", &Cpu::SBC, &Cpu::ABY, 4 },	{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 }, { "???", &Cpu::XXX, &Cpu::IMP, 7 },
			{ "???", &Cpu::NOP, &Cpu::IMP, 4 },	{ "SBC", &Cpu::SBC, &Cpu::ABX, 4 }, { "INC", &Cpu::INC, &Cpu::ABX, 7 },
			{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		};
	}

	Cpu::~Cpu()
	{

	}

	std::uint8_t Cpu::read(std::uint16_t a)
	{
		return bus->read(a, false);
	}

	void Cpu::write(std::uint16_t a, std::uint8_t d)
	{
		bus->write(a, d);
	}


	void Cpu::clock()
	{
		if (cycles == 0) {
			opcode = Cpu::read(pc++);

			cycles = instructions[opcode].cycles;

			//Run address mode and operation functions
			//Returns any additional cycels we need to wait
			std::uint8_t addr_mode_add_cycles = (this->*instructions[opcode].addrmode)();
			std::uint8_t operation_add_cycles = (this->*instructions[opcode].operate)();

			cycles += addr_mode_add_cycles + operation_add_cycles;
		}

		cycles--;

	}

	void Cpu::reset()
	{
		std::uint16_t lo = Cpu::read(0xfffc);
		std::uint16_t hi = Cpu::read(0xfffd);

		pc = (hi << 8) | lo;

		a = 0;
		x = 0;
		y = 0;
		stack = 0xfd;
		status = 0x00 | U;

		addr = 0x0000;
		addr_rel = 0x0000;
		fetched = 0x00;

		cycles = 8;
	}

	void Cpu::irq()
	{
		if (GetFlag(I)) {
			return;
		}

		PushStack((pc >> 8) & 0x00ff);
		PushStack((pc & 0x00ff));
		
		SetFlag(B, false);
		SetFlag(U, true);
		SetFlag(I, true);
		PushStack(status);

		uint16_t lo = Cpu::read(0xfffe);
		uint16_t hi = Cpu::read(0xffff);
		pc = (hi << 8) | lo;

		cycles = 7;
	}

	void Cpu::nmi()
	{
		PushStack((pc >> 8) & 0x00ff);
		PushStack((pc & 0x00ff));
		
		SetFlag(B, false);
		SetFlag(U, true);
		SetFlag(I, true);
		PushStack(status);

		uint16_t lo = Cpu::read(0xfffa);
		uint16_t hi = Cpu::read(0xfffb);
		pc = (hi << 8) | lo;

		cycles = 8;
	}

	std::uint8_t Cpu::GetFlag(FLAGS f)
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

	void Cpu::PushStack(std::uint8_t d)
	{
		Cpu::write(0x0100 + stack--, d);
	}

	std::uint8_t Cpu::PopStack()
	{
		return Cpu::read(0x0100 + stack++);
	}

	std::uint8_t Cpu::fetch()
	{
		if (instructions[opcode].addrmode != &Cpu::IMP) {
			fetched = Cpu::read(addr);
		}
		return fetched;
	}

	// ADDRESSING MODES

	// Absolute
	std::uint8_t Cpu::ABS()
	{
		std::uint8_t lo = Cpu::read(pc++);
		std::uint8_t hi = Cpu::read(pc++);
		addr = (hi << 8) | lo;
		return 0;
	}

	// Absolute indexed with X
	std::uint8_t Cpu::ABX()
	{
		std::uint8_t lo = Cpu::read(pc++);
		std::uint8_t hi = Cpu::read(pc++);
		addr = ((hi << 8) | lo) + x;
		return 0;
	}

	// Absolute indexed with Y
	std::uint8_t Cpu::ABY()
	{
		std::uint8_t lo = Cpu::read(pc++);
		std::uint8_t hi = Cpu::read(pc++);
		addr = ((hi << 8) | lo) + y;
		return 0;
	}

	// Immediate
	std::uint8_t Cpu::IMM()
	{
		addr = pc++;
		return 0;
	}

	// Implied
	std::uint8_t Cpu::IMP()
	{
		addr = a;
		return 0;
	}

	// Indirect
	std::uint8_t Cpu::IND()
	{
		std::uint8_t lo = Cpu::read(pc++);
		std::uint8_t hi = Cpu::read(pc++);
		addr = Cpu::read((hi << 8) | lo);
		return 0;
	}

	// Indirect indexed with X
	std::uint8_t Cpu::IZX()
	{
		addr = Cpu::read(Cpu::read(pc++)) + x;
		return 0;
	}

	// Indirect indexed with Y
	std::uint8_t Cpu::IZY()
	{
		addr = Cpu::read(Cpu::read(pc++)) + y;
		return 0;
	}

	//X indexed Indirect
	std::uint8_t Cpu::XIZ()
	{
		addr = Cpu::read(Cpu::read(pc++) + x);
		return 0;
	}

	//Y indexed Indirect
	std::uint8_t Cpu::YIZ()
	{
		addr = Cpu::read(Cpu::read(pc++) + y);
		return 0;
	}

	// Relative
	std::uint8_t Cpu::REL()
	{
		uint16_t temp_addr = pc;
		addr_rel = temp_addr + Cpu::read(pc);
		pc = temp_addr + 1;
		return 0;
	}

	// Zero paged indexed
	std::uint8_t Cpu::ZP0()
	{
		addr = Cpu::read(pc++);
		return 0;
	}

	// Zero page indexed with X
	std::uint8_t Cpu::ZPX()
	{
		addr = Cpu::read(pc++) + x;
		return 0;
	}

	// Zero page indexed with Y
	std::uint8_t Cpu::ZPY()
	{
		addr = Cpu::read(pc++) + y;
		return 0;
	}
	// ==============================
	// ========== OPCODES ==========
	// ==============================

	//Add with Carry
	std::uint8_t Cpu::ADC()
	{
		temp = (std::uint16_t) a + (std::uint16_t) fetch() + (std::uint16_t) GetFlag(C);
		SetFlag(C, temp & 0xff00);
		SetFlag(N, temp & 0x0080);
		SetFlag(V, (~((std::uint16_t) a ^ (std::uint16_t) fetched) 
			& ((std::uint16_t) a ^ (std::uint16_t) temp)) & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);
		a = temp & 0x00ff;
		return 0;
	}

	//Bitwise AND
	std::uint8_t Cpu::AND()
	{
		a = a & fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);

		return 0;
	}

	//Arithmetic Shift Left
	std::uint8_t Cpu::ASL()
	{
		fetch();
		
		temp = (std::uint16_t) fetched << 1;
		SetFlag(C, temp & 0xFF00);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, temp == 0x0000);

		if (instructions[opcode].addrmode == &Cpu::IMP) {
			a = temp & 0x00ff;
		}
		else {
			Cpu::write(addr, temp & 0x00ff);
		}

		return 0;
	}

	//Test Bits
	std::uint8_t Cpu::BIT()
	{
		temp = a & fetch();
		SetFlag(V, (1 << 6));
		SetFlag(N, (1 << 7));
		SetFlag(Z, temp == 0x000);

		return 0;
	}

	//Break
	std::uint8_t Cpu::BRK()
	{
		pc++;
		return 0;
	}

	//Compare Accumulator
	std::uint8_t Cpu::CMP()
	{
		fetch();
		
		temp = (std::uint16_t)a - (std::uint16_t)fetched;

		SetFlag(C, a >= fetched);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Compare X Register
	std::uint8_t Cpu::CPX()
	{
		fetch();
		
		temp = (std::uint16_t)x - (std::uint16_t)fetched;

		SetFlag(C, x >= fetched);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Compare Y Register
	std::uint8_t Cpu::CPY()
	{
		fetch();
		
		temp = (std::uint16_t)y - (std::uint16_t)fetched;

		SetFlag(C, y >= fetched);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Decrement Memory
	std::uint8_t Cpu::DEC()
	{
		fetch();
		
		temp = fetched - 1;
		Cpu::write(addr, temp & 0x00ff);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Bitwise XOR
	std::uint8_t Cpu::EOR()
	{
		a = a ^ fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);

		return 0;
	}

	//Increment Memory
	std::uint8_t Cpu::INC()
	{
		temp = fetch() + 1;
		Cpu::write(addr, temp);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		return 0;
	}

	//Jump
	std::uint8_t Cpu::JMP()
	{
		pc = addr;
		return 0;
	}

	//Jump to Subroutine
	std::uint8_t Cpu::JSR()
	{
		pc--;

		PushStack((pc >> 8) & 0x00ff);
		PushStack(pc & 0x00ff);

		pc = addr;
		return 0;
	}

	//Load Accumulator
	std::uint8_t Cpu::LDA()
	{
		a = fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);
		return 0;
	}

	//Load X Register
	std::uint8_t Cpu::LDX()
	{
		x = fetch();
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Load Y Register
	std::uint8_t Cpu::LDY()
	{
		y = fetch();
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	//Logical Shift Right
	std::uint8_t Cpu::LSR()
	{
		fetch();

		SetFlag(C, fetched & 0x01);
		fetched = fetched >> 1;
		SetFlag(N, fetched & 0x80);
		SetFlag(Z, fetched == 0x00);
		return 0;
	}

	//No Operation
	std::uint8_t Cpu::NOP()
	{
		return 0;
	}

	//Bitwise OR
	std::uint8_t Cpu::ORA()
	{
		a = a | fetch();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);
		return 0;
	}

	//Rotate Left
	std::uint8_t Cpu::ROL()
	{
		temp = (fetch() << 1) + GetFlag(C);
		SetFlag(C, temp & 0xff00);
		SetFlag(N, temp & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);

		if (instructions[opcode].addrmode == &Cpu::IMP) {
			a = temp & 0x00ff;
		}
		else {
			Cpu::write(addr, temp & 0x00ff);
		}

		return 0;
	}

	//Rotate Right
	std::uint8_t Cpu::ROR()
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
			Cpu::write(addr, temp & 0x00ff);
		}

		return 0;
	}

	//Return from Interrupt
	std::uint8_t Cpu::RTI()
	{
		status = PopStack();
		pc = PopStack();
		return 0;
	}

	//Return from Subroutine
	std::uint8_t Cpu::RTS()
	{
		std::uint8_t lo = PopStack();
		std::uint8_t hi = PopStack();
		pc = ((hi << 8) | lo) + 1;
		return 0;
	}

	//Subtract with Carry
	std::uint8_t Cpu::SBC()
	{
		std::uint16_t flip = ((std::uint16_t) fetch()) ^ 0x00ff;
		temp = (std::uint16_t) a + flip + (std::uint16_t) GetFlag(C);
		SetFlag(C, temp & 0xff00);
		SetFlag(N, temp & 0x0080);
		SetFlag(V, (temp ^ (std::uint16_t)a) & (temp ^ flip) & 0x0080);
		SetFlag(Z, (temp & 0x00ff) == 0x0000);
		a = temp & 0x00ff;
		return 0;
	}

	//Store Accumulator
	std::uint8_t Cpu::STA()
	{
		Cpu::write(addr, a);
		return 0;
	}

	//Store X Register
	std::uint8_t Cpu::STX()
	{
		Cpu::write(addr, x);
		return 0;
	}	
	//Store Y Register
	std::uint8_t Cpu::STY()
	{
		Cpu::write(addr, y);
		return 0;
	}

	// ========================================
	// ========== BRANCH OPCODES ==========
	// ========================================

	//Branch on Plus
	std::uint8_t Cpu::BPL()
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
	std::uint8_t Cpu::BMI()
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
	std::uint8_t Cpu::BVC()
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
	std::uint8_t Cpu::BVS()
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
	std::uint8_t Cpu::BCC()
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
	std::uint8_t Cpu::BCS()
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
	std::uint8_t Cpu::BNE()
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
	std::uint8_t Cpu::BEQ()
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
	std::uint8_t Cpu::CLC()
	{
		SetFlag(C, false);
		return 0;
	}

	//Set Carry
	std::uint8_t Cpu::SEC()
	{
		SetFlag(C, true);
		return 0;
	}

	//Clear Interrupt
	std::uint8_t Cpu::CLI()
	{
		SetFlag(I, false);
		return 0;
	}

	//Set Interrupt
	std::uint8_t Cpu::SEI()
	{
		SetFlag(I, true);
		return 0;
	}

	//Clear Overflow
	std::uint8_t Cpu::CLV()
	{
		SetFlag(V, false);
		return 0;
	}

	//Set Overflow
	std::uint8_t Cpu::SEV()
	{
		SetFlag(V, true);
		return 0;
	}

	//Clear Decimal
	std::uint8_t Cpu::CLD()
	{
		SetFlag(D, false);
		return 0;
	}

	//Set Decimal
	std::uint8_t Cpu::SED()
	{
		SetFlag(D, true);
		return 0;
	}

	// ========================================
	// ========== REGISTER OPCODES ==========
	// ========================================

	//Transfer Accumulator to X
	std::uint8_t Cpu::TAX()
	{
		x = a;
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Transfer X to Accumulator
	std::uint8_t Cpu::TXA()
	{
		a = x;
		SetFlag(N, a & 0x80);
		SetFlag(N, a == 0x00);
		return 0;
	}

	//Decrement X
	std::uint8_t Cpu::DEX()
	{
		x--;
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Increment X
	std::uint8_t Cpu::INX()
	{
		x++;
		SetFlag(N, x & 0x80);
		SetFlag(Z, x == 0x00);
		return 0;
	}

	//Transfer Accumulator to Y
	std::uint8_t Cpu::TAY()
	{
		x = a;
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	//Transfer Y to Accumulator
	std::uint8_t Cpu::TYA()
	{
		a = y;
		SetFlag(N, a & 0x80);
		SetFlag(N, a == 0x00);
		return 0;
	}

	//Decrement Y
	std::uint8_t Cpu::DEY()
	{
		x--;
		SetFlag(N, y & 0x80);
		SetFlag(Z, y == 0x00);
		return 0;
	}

	//Increment Y
	std::uint8_t Cpu::INY()
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
	std::uint8_t Cpu::TXS()
	{
		stack = x;
		return 0;
	}

	//Transfer stack to X
	std::uint8_t Cpu::TSX()
	{
		x = stack;
		return 0;
	}

	//Push Accumulator
	std::uint8_t Cpu::PHA()
	{
		PushStack(a);
		return 0;
	}

	//Pop Accumulator
	std::uint8_t Cpu::PLA()
	{
		a = PopStack();
		SetFlag(N, a & 0x80);
		SetFlag(Z, a == 0x00);
		return 0;
	}

	//Push Processor Status
	std::uint8_t Cpu::PHP()
	{
		PushStack(status | B | U);
		SetFlag(B, 0);
		SetFlag(U, 0);
		return 0;
	}

	//Pop Processor Status
	std::uint8_t Cpu::PLP()
	{
		status = PopStack();
		SetFlag(U, 1);
		return 0;
	}

	//Invalid Opcode
	std::uint8_t Cpu::XXX()
	{
		return 0;
	}
}

