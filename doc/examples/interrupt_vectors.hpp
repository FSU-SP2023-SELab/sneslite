#pragma once

#include<cstdint>

namespace sneslite::cartridge
{
	/**
 	 * Interrupt vector table.
 	 * 
 	 * The SNES stores the interrupt vector table on the first bank of ROM. 
 	 * After execution of an interrupt, the DBR (Data Bank Register) and PBR
 	 * (Program Bank Register) are set to 0.
 	 * 
 	 * Reference:
 	 * https://en.wikibooks.org/wiki/Super_NES_Programming/SNES_memory_map#Interrupt_vectors
 	 */
	struct interrupt_table
	{
		/**
		 * @brief Software interrupt vector
		 * 
		 * Triggered by COP instruction
		 */
		union
		{
			uint16_t cop;
		};

		/**
		 * @brief Software interrupt vector
		 * 
		 * Triggered by BRK instruction
		 */
		union
		{
			uint16_t brk;
		};

		/**
		 * @brief Non-maskable interrupt vector
		 * 
		 * Called when vertical refresh (vblank) begins
		 */
		union
		{
			uint16_t nmi;
		};

		/**
		 * @brief Interrupt request vector
		 * 
		 * Called at certain spots in horizontal refresh cycle
		 */
		union
		{
			uint16_t irq;
		};

		/**
		 * @brief Abort vector
		 * @warning Unused vector
		 */
		union
		{
			uint16_t abort;
		};

		/**
		 * @brief Reset vector
		 * @warning Vector only used in emulation mode
		 * 
		 * Emulation begins at this vector
		 */
		union
		{
			uint16_t res;
		};
	};
}