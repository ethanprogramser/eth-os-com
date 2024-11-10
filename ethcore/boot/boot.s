        .code32

        .set MBOOT_PAGE_ALIGN, (1<<0)
        .set MBOOT_MEM_INFO, (1<<1)
        .set MBOOT_GFX, 0

        .set MBOOT_MAGIC, 0x1BADB002
        .set MBOOT_FLAGS, 0x3
        .set MBOOT_CHECKSUM, -(MBOOT_MAGIC + MBOOT_FLAGS)

        .section .multiboot
        .align 4
        .int MBOOT_MAGIC
        .int MBOOT_FLAGS
        .int MBOOT_CHECKSUM
        .int 0, 0, 0, 0, 0

        .int 0
        .int 800
        .int 600
        .int 32

        .section .bss
        .align 16
stack_bottom:
        .skip 16384 * 8
stack_top:

        .section .boot
        .globl _start
_start:
        movl $(initial_page_dir - 0xC0000000), %ecx
        movl %ecx, %cr3

        movl %cr4, %ecx
        orl $0x10, %ecx
        movl %ecx, %cr4

        movl %cr0, %ecx
        orl $0x80000000, %ecx
        movl %ecx, %cr0

        jmp higher_half

        .section .text
higher_half:
        movl $stack_top, %esp
        pushl %ebx
        pushl %eax
        xorl %ebp, %ebp
        .extern kmain
        call kmain

        cli
        hlt

        .section .data
        .align 4096
        .globl initial_page_dir
initial_page_dir:
        .int 0b10000011
        .rept 768-1
        .int 0
        .endr

        .int (0 << 22) | 0b10000011
        .int (1 << 22) | 0b10000011
        .int (2 << 22) | 0b10000011
        .int (3 << 22) | 0b10000011
        .rept 256-4
        .int 0
        .endr
