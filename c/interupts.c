struct idtr{
short limite;
int base;
} __attribute__((packed));

struct idtdesc {
    short offset0_15;
    short select;
    short type;
    short offset16_31;
} __attribute__((packed));

void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc *desc){
    desc->offset0_15 = (offset & 0xffff);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (offset & 0xffff0000) >> 16;
    return;
}


void init_idt(void)
{
int i;
for (i = 0; i < IDTSIZE; i++){
init_idt_desc(0x08, (u32)_asm_schedule, INTGATE, &kidt[i]); //
    init_idt_desc(0x08, (u32) _asm_exc_GP, INTGATE, &kidt[13]);        /* #GP */
    init_idt_desc(0x08, (u32) _asm_exc_PF, INTGATE, &kidt[14]);     /* #PF */

    init_idt_desc(0x08, (u32) _asm_schedule, INTGATE, &kidt[32]);
    init_idt_desc(0x08, (u32) _asm_int_1, INTGATE, &kidt[33]);

    init_idt_desc(0x08, (u32) _asm_syscalls, TRAPGATE, &kidt[48]);
    init_idt_desc(0x08, (u32) _asm_syscalls, TRAPGATE, &kidt[128]); //48

    kidtr.limite = IDTSIZE * 8;
    kidtr.base = IDTBASE;

    memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

    asm("lidtl (kidtr)");