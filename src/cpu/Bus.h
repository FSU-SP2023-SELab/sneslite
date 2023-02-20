#pragma once
#include "Cpu.h"
#include <cstdint>
#include <array>

namespace sneslite
{

    class Bus
    {
    public:
	    Bus();
	    ~Bus();

	    /**
	     * @brief Devices on the Bus
	     * 
	     */
        Cpu cpu;

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

    };
}
