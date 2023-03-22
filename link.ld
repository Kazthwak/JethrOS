MEMORY{
    ram : ORIGIN = 0x9000, LENGTH = 512K
}

SECTIONS{
.ke : { *(.ke) } > ram
.text : { *(.text) } > ram
.data : { *(.data) } > ram
.bss : { *(.bss) } > ram
.rodata : { *(.rodata) } > ram
. = ALIGN(512);
}
