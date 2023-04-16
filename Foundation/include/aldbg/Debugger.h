//
// Created by achrefabidi on 16/04/23.
//

#pragma once

#include <unistd.h>
#include <string>

namespace aldbg {

    class Debugger {
    public:
        Debugger(std::string progName, pid_t pid);
        virtual ~Debugger();

        void run();

    private:
        pid_t m_debuggeePid;
        std::string m_debuggeeName;
    };
}// end namespace
