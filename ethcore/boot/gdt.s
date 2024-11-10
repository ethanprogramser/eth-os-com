    .globl gdt_flush
gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $.flush
.flush:
    ret

    .globl tss_flush
tss_flush:
    movw $0x2B, %ax
    ltr %ax
    ret
