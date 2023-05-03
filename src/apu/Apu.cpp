#include "Apu.h"

namespace sneslite
{
    Apu::Apu()
    {
        
    }

    Apu::~Apu() 
    {

    }
    
    void Apu::Write(uint16_t addr, uint8_t data)
    {
        switch (addr)
        {
        case 0x4000:
            switch ((data & 0xC0) >> 6)
            {
            case 0x00:
                pulse1_seq.new_sequence = 0b01000000;
                pulse1_osc.dutycycle = 0.125;
                break;
            case 0x01:
                pulse1_seq.new_sequence = 0b01100000;
                pulse1_osc.dutycycle = 0.250;
                break;
            case 0x02:
                pulse1_seq.new_sequence = 0b01111000;
                pulse1_osc.dutycycle = 0.500;
                break;
            case 0x03:
                pulse1_seq.new_sequence = 0b10011111;
                pulse1_osc.dutycycle = 0.750;
                break;
            }
            pulse1_seq.sequence = pulse1_seq.new_sequence;
            pulse1_halt = (data & 0x20);
            pulse1_env.volume = (data & 0x0F);
            pulse1_env.disable = (data & 0x10);
            break;

        case 0x4001:
            pulse1_sweep.enabled = data & 0x80;
            pulse1_sweep.period = (data & 0x70) >> 4;
            pulse1_sweep.down = data & 0x08;
            pulse1_sweep.shift = data & 0x07;
            pulse1_sweep.reload = true;
            break;

        case 0x4002:
            pulse1_seq.reload = (pulse1_seq.reload & 0xFF00) | data;
            break;

        case 0x4003:
            pulse1_seq.reload = (uint16_t)((data & 0x07)) << 8 | (pulse1_seq.reload & 0x00FF);
            pulse1_seq.timer = pulse1_seq.reload;
            pulse1_seq.sequence = pulse1_seq.new_sequence;
            pulse1_lc.counter = length_table[(data & 0xF8) >> 3];
            pulse1_env.start = true;
            break;

        case 0x4004:
            switch ((data & 0xC0) >> 6)
            {
            case 0x00:
                pulse2_seq.new_sequence = 0b01000000;
                pulse2_osc.dutycycle = 0.125;
                break;
            case 0x01:
                pulse2_seq.new_sequence = 0b01100000;
                pulse2_osc.dutycycle = 0.250;
                break;
            case 0x02:
                pulse2_seq.new_sequence = 0b01111000;
                pulse2_osc.dutycycle = 0.500;
                break;
            case 0x03:
                pulse2_seq.new_sequence = 0b10011111;
                pulse2_osc.dutycycle = 0.750;
                break;
            }
            pulse2_seq.sequence = pulse2_seq.new_sequence;
            pulse2_halt = (data & 0x20);
            pulse2_env.volume = (data & 0x0F);
            pulse2_env.disable = (data & 0x10);
            break;

        case 0x4005:
            pulse2_sweep.enabled = data & 0x80;
            pulse2_sweep.period = (data & 0x70) >> 4;
            pulse2_sweep.down = data & 0x08;
            pulse2_sweep.shift = data & 0x07;
            pulse2_sweep.reload = true;
            break;

        case 0x4006:
            pulse2_seq.reload = (pulse2_seq.reload & 0xFF00) | data;
            break;

        case 0x4007:
            pulse2_seq.reload = (uint16_t)((data & 0x07)) << 8 | (pulse2_seq.reload & 0x00FF);
            pulse2_seq.timer = pulse2_seq.reload;
            pulse2_seq.sequence = pulse2_seq.new_sequence;
            pulse2_lc.counter = length_table[(data & 0xF8) >> 3];
            pulse2_env.start = true;

            break;

        case 0x4008:
            break;

        case 0x400C:
            noise_env.volume = (data & 0x0F);
            noise_env.disable = (data & 0x10);
            noise_halt = (data & 0x20);
            break;

        case 0x400E:
            switch (data & 0x0F)
            {
            case 0x00:
                noise_seq.reload = 0;
                break;
            case 0x01:
                noise_seq.reload = 4;
                break;
            case 0x02:
                noise_seq.reload = 8;
                break;
            case 0x03:
                noise_seq.reload = 16;
                break;
            case 0x04:
                noise_seq.reload = 32;
                break;
            case 0x05:
                noise_seq.reload = 64;
                break;
            case 0x06:
                noise_seq.reload = 96;
                break;
            case 0x07:
                noise_seq.reload = 128;
                break;
            case 0x08:
                noise_seq.reload = 160;
                break;
            case 0x09:
                noise_seq.reload = 202;
                break;
            case 0x0A:
                noise_seq.reload = 254;
                break;
            case 0x0B:
                noise_seq.reload = 380;
                break;
            case 0x0C:
                noise_seq.reload = 508;
                break;
            case 0x0D:
                noise_seq.reload = 1016;
                break;
            case 0x0E:
                noise_seq.reload = 2034;
                break;
            case 0x0F:
                noise_seq.reload = 4068;
                break;
            }
            break;

        case 0x4015: // APU STATUS
            pulse1_enable = data & 0x01;
            pulse2_enable = data & 0x02;
            noise_enable = data & 0x04;
            break;

        case 0x400F:
            pulse1_env.start = true;
            pulse2_env.start = true;
            noise_env.start = true;
            noise_lc.counter = length_table[(data & 0xF8) >> 3];
            break;
        }
    }

    uint8_t Apu::Read(uint16_t addr)
    {
        uint8_t data = 0x00;
        return data;
    }

    void Apu::clock()
    {
        bool QuarterClock = false;
        bool HalfClock = false;

        GlobalTime += (0.3333333333 / 1789773);

        if (Clockcount % 6 == 0)
        {
            FrameClockcount++;

            // 4-Step Sequence Mode
            if (FrameClockcount == 3729)
            {
                QuarterClock = true;
            }

            if (FrameClockcount == 7457)
            {
                QuarterClock = true;
                HalfClock = true;
            }

            if (FrameClockcount == 11186)
            {
                QuarterClock = true;
            }

            if (FrameClockcount == 14916)
            {
                QuarterClock = true;
                HalfClock = true;
                FrameClockcount = 0;
            }

            if (QuarterClock)
            {
                pulse1_env.clock(pulse1_halt);
                pulse2_env.clock(pulse2_halt);
                noise_env.clock(noise_halt);
            }

            if (HalfClock)
            {
                pulse1_lc.clock(pulse1_enable, pulse1_halt);
                pulse2_lc.clock(pulse2_enable, pulse2_halt);
                noise_lc.clock(noise_enable, noise_halt);
                pulse1_sweep.clock(pulse1_seq.reload, 0);
                pulse2_sweep.clock(pulse2_seq.reload, 1);
            }

            noise_seq.clock(noise_enable, [](uint32_t &s)
			{
				s = (((s & 0x0001) ^ ((s & 0x0002) >> 1)) << 14) | ((s & 0x7FFF) >> 1);
			});

		    if (noise_lc.counter > 0 && noise_seq.timer >= 8)
		    {
			    noise_output = (double)noise_seq.output * ((double)(noise_env.output-1) / 16.0);
		    }

		    if (!pulse1_enable) pulse1_output = 0;
		    if (!pulse2_enable) pulse2_output = 0;
		    if (!noise_enable) noise_output = 0;

	    }

	    pulse1_sweep.track(pulse1_seq.reload);
	    pulse2_sweep.track(pulse2_seq.reload);

	    Clockcount++;
    }

    double Apu::GetSample()
    {
		return ((1.0 * pulse1_output) - 0.8) * 0.1 + ((1.0 * pulse2_output) - 0.8) * 0.1 + ((2.0 * (noise_output - 0.5))) * 0.1;
    }
}