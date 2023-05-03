#pragma once

#include <cstdint>
#include <functional>

namespace sneslite
{

    class Bus;

    class Apu
    {
        public:
            Apu();
            ~Apu();

            void Write(uint16_t addr, uint8_t data);
            uint8_t Read(uint16_t addr);
            void clock();
            void ConnectBus(Bus* n) { bus = n; }

            double GetSample();

            std::vector<uint8_t> length_table;

        private:

        Bus* bus = nullptr;

        uint32_t Clockcount = 0;
        uint32_t FrameClockcount = 0;

        struct sequencer
	    {
		    uint32_t sequence = 0x00000000;
		    uint32_t new_sequence = 0x00000000;
		    uint16_t timer = 0x0000;
		    uint16_t reload = 0x0000;
		    uint8_t output = 0x00;

		    uint8_t clock(bool bEnable, std::function<void(uint32_t &s)> funcManip)
		    {
			    if (bEnable)
			    {
				    timer--;
				    if (timer == 0xFFFF)
				    {
					    timer = reload;
					    funcManip(sequence);
					    output = sequence & 0x00000001;
				    }
			    }
			    return output;
		    }
	    };

        struct lengthcounter
        {
            uint8_t counter = 0x00;
            uint8_t clock(bool bEnable, bool bHalt)
            {
                if (!bEnable)
                    counter = 0;
                else if (counter > 0 && !bHalt)
                    counter--;
                return counter;
            }
        };

        struct envelope
        {
            void clock(bool bLoop)
            {
                if (!start)
                {
                    if (divider_count == 0)
                    {
                        divider_count = volume;

                        if (decay_count == 0)
                        {
                            if (bLoop)
                            {
                                decay_count = 15;
                            }
                        }
                        else
                            decay_count--;
                    }
                    else
                        divider_count--;
                }
                else
                {
                    start = false;
                    decay_count = 15;
                    divider_count = volume;
                }

                if (disable)
                {
                    output = volume;
                }
                else
                {
                    output = decay_count;
                }
            }

            bool start = false;
            bool disable = false;
            uint16_t divider_count = 0;
            uint16_t volume = 0;
            uint16_t output = 0;
            uint16_t decay_count = 0;
        };

        struct oscpulse
        {
            double frequency = 0;
            double dutycycle = 0;
            double amplitude = 1;
            double pi = 3.14159;
            double harmonics = 20;

            double sample(double t)
            {
                double a = 0;
                double b = 0;
                double p = dutycycle * 2.0 * pi;

                auto approxsin = [](double t)
                {
                    double j = t * 0.15915;
                    j = j - (int)j;
                    return 20.785 * j * (j - 0.5) * (j - 1.0);
                };

                for (double n = 1; n < harmonics; n++)
                {
                    double c = n * frequency * 2.0 * pi * t;
                    a += -approxsin(c) / n;
                    b += -approxsin(c - p * n) / n;

                    // a += -sin(c) / n;
                    // b += -sin(c - p * n) / n;
                }

                return (2.0 * amplitude / pi) * (a - b);
            }
        };

        struct sweeper
        {
            bool enabled = false;
            bool down = false;
            bool reload = false;
            uint8_t shift = 0x00;
            uint8_t timer = 0x00;
            uint8_t period = 0x00;
            uint16_t change = 0;
            bool mute = false;

            void track(uint16_t &target)
            {
                if (enabled)
                {
                    change = target >> shift;
                    mute = (target < 8) || (target > 0x7FF);
                }
            }

            bool clock(uint16_t &target, bool channel)
            {
                bool changed = false;
                if (timer == 0 && enabled && shift > 0 && !mute)
                {
                    if (target >= 8 && change < 0x07FF)
                    {
                        if (down)
                        {
                            target -= change - channel;
                        }
                        else
                        {
                            target += change;
                        }
                        changed = true;
                    }
                }

                return changed;
            }
        };

        double GlobalTime = 0.0;

	    bool pulse1_enable = false;
	    bool pulse1_halt = false;
	    double pulse1_sample = 0.0;
	    double pulse1_output = 0.0;
	    sequencer pulse1_seq;
	    oscpulse pulse1_osc;
	    envelope pulse1_env;
	    lengthcounter pulse1_lc;
	    sweeper pulse1_sweep;

	    bool pulse2_enable = false;
	    bool pulse2_halt = false;
	    double pulse2_sample = 0.0;
	    double pulse2_output = 0.0;
	    sequencer pulse2_seq;
	    oscpulse pulse2_osc;
	    envelope pulse2_env;
	    lengthcounter pulse2_lc;
	    sweeper pulse2_sweep;

	    bool noise_enable = false;
	    bool noise_halt = false;
	    envelope noise_env;
	    lengthcounter noise_lc;
	    sequencer noise_seq;
	    double noise_sample = 0;
	    double noise_output = 0;

    };
}