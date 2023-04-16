//
// Created by achrefabidi on 15/04/23.
//

#include <iostream>
#include<unistd.h>       //< For fork()
#include <sys/ptrace.h>  //< For ptrace()
#include "linenoise.h"
#include "Debugger.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Program name not specified";
        return EXIT_FAILURE;
    }

    auto prog = argv[1];

    auto pid = fork();
    if (pid == 0) {//we're in the child process
        // PTRACE_TRACEME request tells us that: "hey i wanna be traced"
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        //execute debugee
        execl(prog, prog, nullptr);
        //todo: check if execl works fine
    } else if (pid >= 1) {//we're in the parent process
        //execute debugger
        //debugger dbg{prog, pid};
        //dbg.run();

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
}