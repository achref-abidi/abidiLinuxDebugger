
set(ALDBG_SRC
        src/Debugger.cpp
        src/Launcher.cpp
        )

set(ALDBG_INC
        include/aldbg
        )

APPEND_FUNC(ALDBG_SRC)
set(ALDBG_SRC ${ALDBG_SRC} PARENT_SCOPE)

APPEND_FUNC(ALDBG_INC)
set(ALDBG_INC ${ALDBG_INC} PARENT_SCOPE)