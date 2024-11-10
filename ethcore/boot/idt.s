    .globl idt_flush
idt_flush:
    movl 4(%esp), %eax
    lidt (%eax)
    sti
    ret

    .globl isr0
isr0:
    cli
    pushl $0
    pushl $0
    jmp isr_common_stub

    .globl isr1
isr1:
    cli
    pushl $0
    pushl $1
    jmp isr_common_stub

    .globl isr2
isr2:
    cli
    pushl $0
    pushl $2
    jmp isr_common_stub

    .globl isr3
isr3:
    cli
    pushl $0
    pushl $3
    jmp isr_common_stub

    .globl isr4
isr4:
    cli
    pushl $0
    pushl $4
    jmp isr_common_stub

    .globl isr5
isr5:
    cli
    pushl $0
    pushl $5
    jmp isr_common_stub

    .globl isr6
isr6:
    cli
    pushl $0
    pushl $6
    jmp isr_common_stub

    .globl isr7
isr7:
    cli
    pushl $0
    pushl $7
    jmp isr_common_stub

    .globl isr8
isr8:
    cli
    pushl $8
    jmp isr_common_stub

    .globl isr9
isr9:
    cli
    pushl $0
    pushl $9
    jmp isr_common_stub

    .globl irq0
irq0:
    cli
    pushl $0
    pushl $32
    jmp irq_common_stub

    .globl irq1
irq1:
    cli
    pushl $0
    pushl $33
    jmp irq_common_stub

    .globl irq2
irq2:
    cli
    pushl $0
    pushl $34
    jmp irq_common_stub

    .globl irq3
irq3:
    cli
    pushl $0
    pushl $35
    jmp irq_common_stub

    .globl irq4
irq4:
    cli
    pushl $0
    pushl $36
    jmp irq_common_stub

    .extern isr_handler
isr_common_stub:
    pusha
    movl %ds, %eax
    pushl %eax
    movl %cr2, %eax
    pushl %eax

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp
    call isr_handler

    addl $8, %esp
    popl %ebx
    movw %bx, %ds
    movw %bx, %es
    movw %bx, %fs
    movw %bx, %gs

    popa
    addl $8, %esp
    sti
    iret

    .extern irq_handler
irq_common_stub:
    pusha
    movl %ds, %eax
    pushl %eax
    movl %cr2, %eax
    pushl %eax

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp
    call irq_handler

    addl $8, %esp
    popl %ebx
    movw %bx, %ds
    movw %bx, %es
    movw %bx, %fs
    movw %bx, %gs

    popa
    addl $8, %esp
    sti
    iret
