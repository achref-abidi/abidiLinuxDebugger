# Project Tutorial
This project was done following this tutorial:
[Writing a linux debugger](https://blog.tartanllama.xyz/writing-a-linux-debugger-setup/#fn:1)

# Used dependencies
- [linenoise](https://github.com/antirez/linenoise).
It is a replacement for GNU readline and libedit.
That provides in-line editing and history capabilities for interactive programs with a command-line interface, such as Bash.
It allows users to move the text cursor, search the command history, control a kill ring 
(a more flexible version of a copy/paste clipboard) and use tab completion on a text terminal.
- [Libelfin](https://github.com/TartanLlama/libelfin/tree/fbreg) is a from-scratch C++11 library for reading ELF binaries and DWARFv4 debug information.

# Sources
- https://en.wikipedia.org/wiki/GNU_Readline#External_links