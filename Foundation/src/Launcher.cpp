//
// Created by achrefabidi on 15/04/23.
//

#include <iostream>
#include <unistd.h>     //< For fork()
#include <sys/ptrace.h> //< For ptrace()
#include <errno.h>      //< for errno
#include <string.h>     //< For strerror_r()
#include "Debugger.h"

int main(int argc, char *argv[])
{
    std::string prog;
#ifdef _NDEBUG
    if (argc < 2)
    {
        std::cerr << "Program name was not specified";
        return EXIT_FAILURE;
    }
    prog = argv[1];
#else
    prog = "./Debugee";
#endif

    auto pid = fork();
    if (pid == 0)
    {
        // we're in the child process
        int statusCode;
        // PTRACE_TRACEME request tells us that: "hey i wanna be traced"
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        // execute debugee
        statusCode = execl(prog.c_str(), prog.c_str(), nullptr);
        if (statusCode == -1)
        {
            std::cout << "Child terminated Incorrectely" << std::endl;
            char buffer[256];
            char *errorMsg = strerror_r(errno, buffer, 256);         // GNU-specific version, Linux default
            std::cout << "Error message: " << errorMsg << std::endl; // return value has to be used since buffer might not be modified
            return EXIT_FAILURE;                                     // To send error to the parent proc.
        }
    }
    else if (pid >= 1)
    {
        // we're in the parent process
        // execute debugger
        aldbg::Debugger dbg{prog, pid};
        dbg.run();

        /**
         * @note the child won't get here because we called exec()
         * also we use `wait()` to wait for the end of the child process, because ptrace won't work for an
         * orphan child, and also the parent should always be present to handle the debugging process.
         *
         * @note something is quite ambiguous, haw do we handle debugging, if the parent process is blocked waiting
         * for the child process to terminate? even if child process is blocked, the parent process will still be
         * blocked.
         *
         * @clarification Waiting causes the parent to wait for the child to alter its state. The status change
         * could be due to the child process being terminated, stopped by a signal, or resumed by a signal.
         * When the traced process is launched, it will be sent a SIGTRAP signal, which is a trace or breakpoint trap.
         * We can wait until this signal is sent using the waitpid function.
         */
    }
    else
    {
        std::cout << "Failed to fork!\n";
    }
}