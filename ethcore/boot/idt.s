        .globl  idt_flush
idt_flush:
        movl 4(%esp), %eax
        lidtl (%eax)
        sti
        ret

        # ISR
        .globl  isr0
isr0:
        cli
        pushl   $0
        pushl   $0
        jmp     isr_common_stub

        .globl  isr1
isr1:
        cli
        pushl   $0
        pushl   $1
        jmp     isr_common_stub

        .globl  isr2
isr2:
        cli
        pushl   $0
        pushl   $2
        jmp     isr_common_stub

        .globl  isr3
isr3:
        cli
        pushl   $0
        pushl   $3
        jmp     isr_common_stub

        .globl  isr4
isr4:
        cli
        pushl   $0
        pushl   $4
        jmp     isr_common_stub

        .globl  isr5
isr5:
        cli
        pushl   $0
        pushl   $5
        jmp     isr_common_stub

        .globl  isr6
isr6:
        cli
        pushl   $0
        pushl   $6
        jmp     isr_common_stub

        .globl  isr7
isr7:
        cli
        pushl   $0
        pushl   $7
        jmp     isr_common_stub

        .globl  isr8
isr8:
        cli
        pushl   $8
        jmp     isr_common_stub

        .globl  isr9
isr9:
        cli
        pushl   $0
        pushl   $9
        jmp     isr_common_stub

        .globl  isr10
isr10:
        cli
        pushl   $10
        jmp     isr_common_stub

        .globl  isr11
isr11:
        cli
        pushl   $11
        jmp     isr_common_stub

        .globl  isr12
isr12:
        cli
        pushl   $12
        jmp     isr_common_stub

        .globl  isr13
isr13:
        cli
        pushl   $13
        jmp     isr_common_stub

        .globl  isr14
isr14:
        cli
        pushl   $14
        jmp     isr_common_stub

        .globl  isr15
isr15:
        cli
        pushl   $0
        pushl   $15
        jmp     isr_common_stub

        .globl  isr16
isr16:
        cli
        pushl   $0
        pushl   $16
        jmp     isr_common_stub

        .globl  isr17
isr17:
        cli
        pushl   $0
        pushl   $17
        jmp     isr_common_stub

        .globl  isr18
isr18:
        cli
        pushl   $0
        pushl   $18
        jmp     isr_common_stub

        .globl  isr19
isr19:
        cli
        pushl   $0
        pushl   $19
        jmp     isr_common_stub

        .globl  isr20
isr20:
        cli
        pushl   $0
        pushl   $20
        jmp     isr_common_stub

        .globl  isr21
isr21:
        cli
        pushl   $0
        pushl   $21
        jmp     isr_common_stub

        .globl  isr22
isr22:
        cli
        pushl   $0
        pushl   $22
        jmp     isr_common_stub

        .globl  isr23
isr23:
        cli
        pushl   $0
        pushl   $23
        jmp     isr_common_stub

        .globl  isr24
isr24:
        cli
        pushl   $0
        pushl   $24
        jmp     isr_common_stub

        .globl  isr25
isr25:
        cli
        pushl   $0
        pushl   $25
        jmp     isr_common_stub

        .globl  isr26
isr26:
        cli
        pushl   $0
        pushl   $26
        jmp     isr_common_stub

        .globl  isr27
isr27:
        cli
        pushl   $0
        pushl   $27
        jmp     isr_common_stub

        .globl  isr28
isr28:
        cli
        pushl   $0
        pushl   $28
        jmp     isr_common_stub

        .globl  isr29
isr29:
        cli
        pushl   $0
        pushl   $29
        jmp     isr_common_stub

        .globl  isr30
isr30:
        cli
        pushl   $0
        pushl   $30
        jmp     isr_common_stub

        .globl  isr31
isr31:
        cli
        pushl   $0
        pushl   $31
        jmp     isr_common_stub

        .globl  isr128
isr128:
        cli
        pushl   $0
        pushl   $128
        jmp     isr_common_stub

        .globl  isr177
isr177:
        cli
        pushl   $0
        pushl   $177
        jmp     isr_common_stub

        .extern isr_handler
isr_common_stub:
        pusha
        movl    %ds, %eax
        pushl   %eax
        movl    %cr2, %eax
        pushl   %eax

        movw    $0x10, %ax
        movw    %ax, %ds
        movw    %ax, %es
        movw    %ax, %fs
        movw    %ax, %gs

        pushl   %esp
        call    isr_handler

        addl    $8, %esp
        popl    %ebx
        movw    %bx, %ds
        movw    %bx, %es
        movw    %bx, %fs
        movw    %bx, %gs

        popa
        addl    $8, %esp
        sti
        iret

        # IRQ
        .globl  irq0
irq0:
        cli
        pushl   $0
        pushl   32
        jmp     irq_common_stub

        .globl  irq1
irq1:
        cli
        pushl   $0
        pushl   33
        jmp     irq_common_stub

        .globl  irq2
irq2:
        cli
        pushl   $0
        pushl   34
        jmp     irq_common_stub

        .globl  irq3
irq3:
        cli
        pushl   $0
        pushl   35
        jmp     irq_common_stub

        .globl  irq4
irq4:
        cli
        pushl   $0
        pushl   36
        jmp     irq_common_stub

        .globl  irq5
irq5:
        cli
        pushl   $0
        pushl   37
        jmp     irq_common_stub

        .globl  irq6
irq6:
        cli
        pushl   $0
        pushl   38
        jmp     irq_common_stub

        .globl  irq7
irq7:
        cli
        pushl   $0
        pushl   39
        jmp     irq_common_stub

        .globl  irq8
irq8:
        cli
        pushl   $0
        pushl   40
        jmp     irq_common_stub

        .globl  irq9
irq9:
        cli
        pushl   $0
        pushl   41
        jmp     irq_common_stub

        .globl  irq10
irq10:
        cli
        pushl   $0
        pushl   42
        jmp     irq_common_stub

        .globl  irq11
irq11:
        cli
        pushl   $0
        pushl   43
        jmp     irq_common_stub

        .globl  irq12
irq12:
        cli
        pushl   $0
        pushl   44
        jmp     irq_common_stub

        .globl  irq13
irq13:
        cli
        pushl   $0
        pushl   45
        jmp     irq_common_stub

        .globl  irq14
irq14:
        cli
        pushl   $0
        pushl   46
        jmp     irq_common_stub

        .globl  irq15
irq15:
        cli
        pushl   $0
        pushl   47
        jmp     irq_common_stub

        .extern irq_handler
irq_common_stub:
        pusha
        movl    %ds, %eax
        pushl   %eax
        movl    %cr2, %eax
        pushl   %eax

        movw    $0x10, %ax
        movw    %ax, %ds
        movw    %ax, %es
        movw    %ax, %fs
        movw    %ax, %gs

        pushl   %esp
        call    irq_handler

        addl    $8, %esp
        popl    %ebx
        movw    %bx, %ds
        movw    %bx, %es
        movw    %bx, %fs
        movw    %bx, %gs

        popa
        addl    $8, %esp
        sti
        iret
