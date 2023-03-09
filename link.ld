MEMORY{
    ram : ORIGIN = 0x7e00, LENGTH = 512K
    idt : ORIGIN = 0x700, LENGTH = 3K
}

SECTIONS{
.idt : { *(.idt) } > idt
.ke : { *(.ke) } > ram
.text : { *(.text) } > ram
.data : { *(.data) } > ram
.bss : { *(.bss) } > ram
.rodata : { *(.rodata) } > ram
. = ALIGN(512);
}
