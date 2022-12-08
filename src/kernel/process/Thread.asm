[GLOBAL Thread_switch]
[GLOBAL Thread_start]

[SECTION .text]

;; Starts or continues a thread
Thread_start:
    ;; NOTE: Starting/Continuing a thread works like this:
    ;;       1. When preparing a new thread the stack is prepared manually to contain the
    ;;          address of the "kickoff" function in place of the return address and the
    ;;          thread's stack registers. The "esp" member variable points to this stack
    ;;       2. When a running thread is paused (because of preemption), the registers are pushed
    ;;          and the stack looks the same way
    ;;       3. When a thread should be started or continued this function is called, during the call
    ;;          the argument (the stack pointer) and return address will be pushed to the stack
    ;;       4. Load the pushed stack pointer to switch the stack (leave the current stack and use
    ;;          the stack of the thread that should be started/continued
    ;;       5. Load all the registers that were prepared/saved beforehand
    ;;       6. Call return, this jumps either to kickoff (if the thread is started for the first time)
    ;;          or to the last execution position before the thread was paused

    ;; == High address ==
    ;;        ESP
    ;; SP --> RET ADDR
    ;; == Low address ==

    mov esp, [esp + 0x4]
    ;; == High address ==
    ;;        *OBJECT
    ;;        0x13115
    ;;        *KICKOFF
    ;;        EAX
    ;;        ECX
    ;;        EDX
    ;;        EBX
    ;;        ESP
    ;;        EBP
    ;;        ESI
    ;;        EDI
    ;; SP --> EFLAGS
    ;; == Low address ==

    popf
    popa
    ;; == High address ==
    ;;        *OBJECT
    ;;        0x13115
    ;; SP --> *KICKOFF
    ;; == Low address ==

    sti
    ret

;; Store the current thread's state and continue with another thread
Thread_switch:
    ;; NOTE: The thread switching works like this:
    ;;       1. Prev thread is running, timer interrupt triggers preemption, interrupt handler called
    ;;       2. This function is called (with the call the return address where the execution should resume
    ;;          when switching back to the prev thread is pushed to the stack)
    ;;       3. Prev registers are pushed to the stack after the return address
    ;;          The prev thread's stack pointer is also saved (to the thread's esp member variable)
    ;;       4. Switch to next stack by loading the esp of the next thread (leave current stack, we will switch
    ;;          back to it when resuming the prev thread, this is possible because we saved the stack pointer
    ;;          to the thread instance)
    ;;       5. Registers are popped from stack, the esp now points
    ;;          to the return address (that was written to the stack when it
    ;;          was switched from)
    ;;       6. Return follows the return address to resume normal stack execution

    ;; == High address ==
    ;;        ESP_NEXT
    ;;        *ESP_PREV
    ;; SP --> RET ADDR
    ;; == Low address ==

    pusha
    pushf
    ;; == High address ==
    ;;        PREV
    ;;        THREAD
    ;;        STACK
    ;; + 0x2c ESP_NEXT
    ;; + 0x28 *ESP_PREV
    ;; + 0x24 RET ADDR
    ;;        EAX
    ;;        ECX
    ;;        EDX
    ;;        EBX
    ;;        ESP
    ;;        EBP
    ;;        ESI
    ;;        EDI
    ;; SP --> EFLAGS
    ;; == Low address ==

    mov eax, [esp + 0x28]       ; Point to *ESP_PREV (Address)
    mov [eax], esp              ; Update thread esp variable

    ;; ============================================================

    mov esp, [esp + 0x2c]        ; Move to next thread's stack
    ;; == High address ==
    ;;        NEW
    ;;        THREAD
    ;;        STACK
    ;;        RET ADDR
    ;;        EAX
    ;;        ECX
    ;;        EDX
    ;;        EBX
    ;;        ESP
    ;;        EBP
    ;;        ESI
    ;;        EDI
    ;; SP --> EFLAGS
    ;; == Low address ==

    popf                        ; Load new registers from stack
    popa
    ;; == High address ==
    ;;        NEW
    ;;        THREAD
    ;;        STACK
    ;; SP --> RET ADDR
    ;; == Low address ==

    ;; Enable interrupts again
    sti
    ret
