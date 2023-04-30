#pragma once

#include "Cpu.h"
#include "../apu/Apu.h"
#include "../ppu/Ppu.hpp"
#include "../cartridge/Cartridge.hpp"

#include <cstdint>
#include <array>
#include <functional>

namespace sneslite
{
    class Bus
    {
    	public:
	    	Bus();

			void begin(std::string path);

			/**
		 	* @brief Cartidge on the bus
		 	* 
		 	*/
			Cartridge cartridge;

	    	/**
	     	* @brief Central processing unit on the Bus
	     	* 
	     	*/
        	Cpu cpu;

			/**
		 	* @brief Picture processing unit on the Bus 
		 	* 
		 	*/
			Ppu ppu;

			/**
		 	* @brief Audio processing unit on the Bus
		 	* 
		 	*/
			Apu apu;

	    	/**
	     	* @brief TEMP fake RAM
	     	* 
	     	*/
	    	std::array<uint8_t, 64 * 1024> ram;

	    	/**
	     	* @brief Bus Read
	     	* 
	     	* @param addr 
	     	* @param data 
	     	*/
	    	void write(uint16_t addr, uint8_t data);
        
        	/**
         	* @brief Bus Write
         	* 
         	* @param addr 
         	* @param bReadOnly 
         	* @return uint8_t 
         	*/
	    	uint8_t read(uint16_t addr, bool bReadOnly = false);

			/**
		 	* @brief Set the Sample Frequency
		 	* 
		 	* @param sample_rate 
		 	*/
			void SetSampleFrequency(uint32_t sample_rate);

			double Sample = 0.0;
		
			/**
		 	* @brief For resets
		 	* 
		 	*/
			void reset();

			/**
		 	* @brief For calculating the clock
		 	* 
		 	* @return true 
		 	* @return false 
		 	*/
			bool clock();

		private:

			double AudioTime = 0.0;
			double AudioTimeNESClock = 0.0;
			double AudioTimeSample = 0.0f;
			uint32_t Clockcount = 0;

			uint8_t dma_page = 0x00;
			uint8_t dma_addr = 0x00;
			uint8_t dma_data = 0x00;
			bool dma_dummy = true;
			bool dma_transfer = false;

			std::function<void(const Ppu&)> gameloop_callback;
    };
}
