//
// Created by achrefabidi on 16/04/23.
//
#include "Debugger.h"

aldbg::Debugger::Debugger(std::string progName, pid_t pid)
: m_debuggeeName(progName), m_debuggeePid(pid)
{}

void aldbg::Debugger::run() {
    int waitStatus;
    int options = 0;
    waitpid(m_debuggeePid, &waitStatus, options);

    //Reading a line from the prompt
    char* line = nullptr;
    while((line = linenoise("aldbg> ")) != nullptr){
        // call handleCommand to handle the user input
        this->handleCommand(line);
        // add command to history
        linenoiseHistoryAdd(line);
        // free the read line
        linenoiseFree(line);
    }
}

void aldbg::Debugger::handleCommand(const std::string& line) {
    std::vector<std::string> args = parseLine(line);
    if(isPrefix(args[0], "continue")){
        continueExecution();
    }
}

std::vector<std::string> aldbg::Debugger::parseLine(const std::string& line) {
    std::istringstream ss{line};
    std::vector<std::string> out;

    for(std::string arg; std::getline(ss, arg, ' ');){
        out.push_back(arg);
    }

    return out;
}

bool aldbg::Debugger::isPrefix(const std::string &s1, const std::string &s2) {
    if(s1.size() > s2.size()) return false;
    return std::equal(s1.begin(), s1.end(), s2.begin());
}

void aldbg::Debugger::continueExecution() {
    // PTRACE_CONT will continue the execution
    ptrace(PTRACE_CONT, m_debuggeePid, nullptr, nullptr);

    int status;
    int options = 0;
    waitpid(m_debuggeePid, &status, options);

}

