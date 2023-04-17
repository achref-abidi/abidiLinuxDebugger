//
// Created by achrefabidi on 17/04/23.
//

#pragma once

#include <sys/types.h>
#include <sys/ptrace.h>
#include <iostream>

namespace aldbg {
    class BreakPoint{
    public:
        static const uint64_t INT3 = 0xCC;

        BreakPoint(pid_t pid, std::intptr_t address);
        virtual ~BreakPoint() = default;

        void enable();
        void disable();

        // to enable a breakpoint
        bool isEnabled() const;

        //to disable a breakpoit
        std::intptr_t getAddress() const;


    private:
        pid_t m_pid;
        std::intptr_t m_address;
        bool m_isEnabled;
        uint8_t m_savedData;
    };
}
