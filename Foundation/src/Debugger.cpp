//
// Created by achrefabidi on 16/04/23.
//
#include "Debugger.h"

aldbg::Debugger::Debugger(std::string progName, pid_t pid)
: m_debuggeeName(progName), m_debuggeePid(pid)
{}

void aldbg::Debugger::run() {
    showInfo();

    int waitStatus;
    waitpid(m_debuggeePid, &waitStatus, 0);

    if(WIFSTOPPED(waitStatus)) {
        //Reading a line from the prompt
        char *line = nullptr;
        while ((line = linenoise("aldbg> ")) != nullptr) {
            // call handleCommand to handle the user input
            this->handleCommand(line);
            // add command to history
            linenoiseHistoryAdd(line);
            // free the read line
            linenoiseFree(line);
        }
    }
}

void aldbg::Debugger::handleCommand(const std::string& line) const {
    std::vector<std::string> args = parseLine(line);
    if(isPrefix(args[0], "continue")){
        continueExecution();
    }else if(isPrefix(args[0], "exit")){
        exit(0); //todo: should kill the child process too.
    }else if(isPrefix(args[0], "help")){
        showHelp();
    }
    else{
        std::cout << args[0] << ": Command is not recognized!\n";
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

void aldbg::Debugger::continueExecution() const{
    // PTRACE_CONT will continue the execution
    ptrace(PTRACE_CONT, m_debuggeePid, nullptr, nullptr);

    int status;
    int options = 0;
    waitpid(m_debuggeePid, &status, options);

}

void aldbg::Debugger::showHelp() {
    std::cout << "continue\tcontinue execution of the program until the next system call.\n";
    std::cout << "help\tdisplay help\n";
    std::cout << "exit\texit the debugger\n";
}

void aldbg::Debugger::showInfo() {
    std::cout << "AbidiLinuxDebugger : is a x86 linux debugger made for learning purposes.\n";
    std::cout << "Press 'h' or 'help' to list out the available command\n\n";
}

