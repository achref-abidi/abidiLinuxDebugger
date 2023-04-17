//
// Created by achrefabidi on 17/04/23.
//
#include "BreakPoint.h"

aldbg::BreakPoint::BreakPoint(pid_t pid, std::intptr_t address)
:   m_pid(pid), m_address(address), m_isEnabled(true), m_savedData{}
{}

bool aldbg::BreakPoint::isEnabled() const{
    return m_isEnabled;
}

std::intptr_t aldbg::BreakPoint::getAddress() const{
    return m_address;
}

void aldbg::BreakPoint::enable() {
    //1. save a copy of the content of m_address (!ptrace operate on a whole word)
    long data = ptrace(PTRACE_PEEKDATA, m_pid, m_address, nullptr);// return a 64 bits address
    m_savedData = static_cast<uint8_t>(data & 0xFF); // we will ust take the Least Significant Byte.

    //2. write `int 3` === 0xCC
    uint64_t dataToInsert = (data & ~0xFF) | INT3;
    ptrace(PTRACE_POKEDATA, m_pid, m_address, dataToInsert);

    m_isEnabled = true;
}

void aldbg::BreakPoint::disable() {
    //Since ptrace operate on a whole data we need to read the MSB and the add to it the saved LSB.
    long data = ptrace(PTRACE_PEEKDATA, m_pid, m_address, nullptr);
    uint64_t dataToInsert = m_savedData | (data & ~0xFF);

    ptrace(PTRACE_POKEDATA, m_pid, m_address, dataToInsert);

    m_isEnabled = false;
}
