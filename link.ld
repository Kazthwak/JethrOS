MEMROY
{
    ram : ORIGIN = 0x7e00
}

SECTIONS
{
.ke = { *(.ke) } > ram
.text = { *(.text) } > ram
.data = { *(.data) } > ram
.bss = { *(.bss) } > ram
. = ALIGN(512);
}
