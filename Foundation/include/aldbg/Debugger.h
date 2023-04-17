//
// Created by achrefabidi on 16/04/23.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

//#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "linenoise.h"

namespace aldbg {

    class Debugger {
    public:
        Debugger(std::string progName, pid_t pid);
        virtual ~Debugger() = default;

        // To run the debugger
        void run();

        // Continue execution of the debuggee until the next signal
        void continueExecution() const;

        // Helper function for parsing a single input line
        static std::vector<std::string> parseLine(const std::string& line);
        // Helper function to check id s1 is a prefix of s2
        static bool isPrefix(const std::string& s1, const std::string& s2);

    protected:
        // User command handler
        void handleCommand(const std::string& line) const;
        static void showHelp() ;
        static void showInfo() ;

    private:
        pid_t m_debuggeePid;
        std::string m_debuggeeName;
    };
}// end namespace
