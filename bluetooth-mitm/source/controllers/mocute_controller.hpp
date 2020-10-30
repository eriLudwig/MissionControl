/*
 * Copyright (C) 2020 ndeadly
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "emulated_switch_controller.hpp"

namespace ams::controller {

    enum MocuteDPadDirection {
        MocuteDPad_N,
        MocuteDPad_NE,
        MocuteDPad_E,
        MocuteDPad_SE,
        MocuteDPad_S,
        MocuteDPad_SW,
        MocuteDPad_W,
        MocuteDPad_NW,
        MocuteDPad_Released = 0x0f
    };

    enum MocuteDPadDirection2 {
        MocuteDPad2_Released = 0x00,
        MocuteDPad2_N,
        MocuteDPad2_NE,
        MocuteDPad2_E,
        MocuteDPad2_SE,
        MocuteDPad2_S,
        MocuteDPad2_SW,
        MocuteDPad2_W,
        MocuteDPad2_NW
    };

    struct MocuteStickData {
        uint8_t x;
        uint8_t y;
    } __attribute__ ((__packed__));

    struct MocuteButtonData {
        uint8_t dpad    : 4;
        uint8_t A       : 1;
        uint8_t B       : 1;
        uint8_t X       : 1;
        uint8_t Y       : 1;

        uint8_t L1      : 1;
        uint8_t R1      : 1;
        uint8_t select  : 1;
        uint8_t start   : 1;
        uint8_t L3      : 1;
        uint8_t R3      : 1;
        uint8_t L2      : 1;
        uint8_t R2      : 1;
    } __attribute__ ((__packed__));

    struct MocuteInputReport0x01 {
        MocuteStickData left_stick;
        MocuteStickData right_stick;
        MocuteButtonData buttons;
        uint8_t left_trigger;
        uint8_t right_trigger;
    } __attribute__ ((__packed__)); 

    typedef MocuteInputReport0x01 MocuteInputReport0x04;

    struct MocuteReportData {
        uint8_t id;
        union {
            MocuteInputReport0x01 input0x01;
            MocuteInputReport0x04 input0x04;
        };
    } __attribute__((packed));

    class MocuteController : public EmulatedSwitchController {

        public:
            static constexpr const HardwareID hardware_ids[] = { 
                {0xffff, 0x0000}    // Mocute 050 Controller
            };  

            MocuteController(const bluetooth::Address *address) 
                : EmulatedSwitchController(address) { };

            void UpdateControllerState(const bluetooth::HidReport *report);

        private:
            void HandleInputReport0x01(const MocuteReportData *src);
            void HandleInputReport0x04(const MocuteReportData *src);

    };

}
