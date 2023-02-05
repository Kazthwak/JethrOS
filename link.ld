MEMORY{
    ram : ORIGIN = 0x7e00, LENGTH = 512K
}

SECTIONS{
.ke : { *(.ke) } > ram
.text : { *(.text) } > ram
.data : { *(.data) } > ram
.bss : { *(.bss) } > ram
. = ALIGN(512);
}
