//this is copy-pasted. I just want something that works
extern void idt_load();


/* Defines an IDT entry */
struct idt_entry{
    uint16_t base_lo;
    uint16_t sel;        /* Our kernel segment goes here! */
    uint8_t always0;     /* This will ALWAYS be set to 0! */
    uint8_t flags;       /* Set using the above table! */
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	uint32_t idt_entry_base = &idt + (num * 8);
    /* The interrupt routine's base address */
    // idt[num].base_lo = (base & 0xFFFF);
	qhexint(&idt_entry_base);
	hang();
	
	uint16_t* base_lo = (uint16_t)idt_entry_base;
	*base_lo = base & 0xffff;
    // idt[num].base_hi = (base >> 16) & 0xFFFF;
	
	uint16_t* sele = (uint16_t)idt_entry_base+2;
	*sele = sel;

	uint8_t* zero = (uint8_t)idt_entry_base+4;
	*zero = 0x00;

	uint8_t* options = (uint8_t)idt_entry_base+5;
	*options = flags;

	uint16_t* base_hi = (uint16_t)idt_entry_base+6;
	*base_hi = (base >> 16) & 0xffff;



    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    // idt[num].sel = sel;
    // idt[num].always0 = 0;
    // idt[num].flags = flags;
}

//copy pasted
/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
	// memset(0x600, 0xff, 2048);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}

void idt_init2(){
idt_install();
idt_set_gate(0, 0xffffffff, 0xffff, 0xff);
qhexint(&idt);
waitforkey();
memdump(&idt);
}