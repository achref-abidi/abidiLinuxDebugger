//
// Created by achrefabidi on 16/04/23.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "linenoise.h"
#include "BreakPoint.h"

namespace aldbg
{

    class Debugger
    {
    public:
        Debugger(std::string progName, pid_t pid);
        virtual ~Debugger() = default;

        // To run the debugger
        void run();

        // Continue execution of the debuggee until the next signal/breakpoint
        void continueExecution() const;

        // set breakpoints
        void setBreakPointAtAddress(std::intptr_t address);

    protected:
        // User command handler
        void handleCommand(const std::string &line);
        static void showHelp();
        static void showInfo();

        // Helper function for parsing a single input line
        static std::vector<std::string> parseLine(const std::string &line);
        // Helper function to check id s1 is a prefix of s2
        static bool isPrefix(const std::string &s1, const std::string &s2);

    private:
        pid_t m_debuggeePid;                                         //< PID of the child process i.e. debugee
        std::string m_debuggeeName;                                  //< Path to the debugee
        std::unordered_map<std::intptr_t, BreakPoint> m_breakPoints; //< table of user defined breakpoints
    };
} // namespace aldbg
