/*****************************************************************************
 *                                                                           *
 *                              C O R O U T I N E                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Koroutinen-Konzepts.               *
 *                  Die Koroutinen sind miteinander verkettet, weswegen die  *
 *                  Klasse Coroutine ein Subtyp von 'Chain' ist.             *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext der Koroutine  *
 *                  eingerichtet. Mit 'start' wird ein Koroutine aktiviert.  *
 *                  Das Umschalten auf die naechste Koroutine erfolgt durch  *
 *                  Aufruf von 'switchToNext'.                               *
 *                                                                           *
 *                  Um bei einem Koroutinenwechsel den Kontext sichern zu    *
 *                  koennen, enthaelt jedes Koroutinenobjekt eine Struktur   *
 *                  CoroutineState, in dem die Werte der nicht-fluechtigen   *
 *                  Register gesichert werden koennen.                       *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 13.08.2020                     *
 *****************************************************************************/

#include "Thread.h"
#include "thread_asm.cpp"

namespace Kernel {

uint16_t ThreadCnt = 8;  // Reserve some IDs that are fixed to specific unique threads

Thread::Thread() : tid(ThreadCnt++), stack(new uint32_t[STACK_SIZE]) {
    if (stack == nullptr) {
        // TODO: Exception
        return;
    }

    // Manually prepare the stack. Because the stack "grows" from top to bottom
    // we need to write at the last addresses
    auto *manual_stack = &stack[STACK_SIZE];

    manual_stack[-1] = reinterpret_cast<uint32_t>(this); // The argument for kickoff is the thread itself
    manual_stack[-2] = 0x131155; // Dummy return address that will never be called ("run" doesn't return)
    manual_stack[-3] = reinterpret_cast<uint32_t>(kickoff); // Return will jump to kickoff
    manual_stack[-4] = 0;                         // EAX
    manual_stack[-5] = 0;                         // ECX
    manual_stack[-6] = 0;                         // EDX
    manual_stack[-7] = 0;                         // EBX
    manual_stack[-8] = reinterpret_cast<uint32_t>(&manual_stack[-3]); // ESP
    manual_stack[-9] = 0;                         // EBP
    manual_stack[-10] = 0;                        // ESI
    manual_stack[-11] = 0;                        // EDI
    manual_stack[-12] = 0x200;                    // EFLAGS

    esp = reinterpret_cast<uint32_t>(&manual_stack[-12]);
}

void Thread::start() const {
    Thread_start(esp);
}

void Thread::switchTo(Thread &next) {
    Thread_switch(&esp, next.esp);
}

[[noreturn]] void Thread::kickoff(Thread *thread) {
    thread->run();

    // TODO: Replace with exception
    // object->run() kehrt (hoffentlich) nie hierher zurueck
    while (true) {}
}

}
