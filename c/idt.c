

#ifndef header
#include <stdint.h>
#endif

//this is copy-pasted. I just want something that works
extern void idt_load();
extern void idt_test();
typedef void func(void);

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
#define idt_start_mem 0x510
#define idtp 0x7000

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	uint32_t idt_entry_base = idt_start_mem + (num * 8);
    /* The interrupt routine's base address */
    // idt[num].base_lo = (base & 0xFFFF);
	// qhexint(idt_start_mem);
	// hang();
	
	uint16_t* base_lo = ((uint16_t*)(idt_entry_base-2))+1;
	*base_lo =  (uint16_t)(base & 0xffff);
    // idt[num].base_hi = (base >> 16) & 0xFFFF;
	
	uint16_t* sele = (uint16_t*)idt_entry_base+1;
	*sele = sel;

	uint8_t* zero = (uint8_t*)idt_entry_base+4;
	*zero = 0x00;

	uint8_t* options = (uint8_t*)idt_entry_base+5;
	*options = 0x8f;

	uint16_t* base_hi = (uint16_t*)idt_entry_base+3;
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
    // idtp->limit = (sizeof (struct idt_entry) * 256) - 1;
    // idtp->base = idt_start_mem-1;

	uint16_t* limit = idtp;
	*limit = (sizeof(struct idt_entry)*256)-1;
	uint32_t* base = (uint32_t*)((uint32_t)idtp + 2);
	*base = idt_start_mem-2;
    
	
	/* Clear out the entire IDT, initializing it to zeros */
    memset(idt_start_mem, 0, sizeof(struct idt_entry) * 256);
	// memset(0x600, 0xff, 2048);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}

void test(){
clear();
setoffset(0,-1);
uint8_t* addrh = idt_start_mem+6-2;
uint8_t* addrl = idt_start_mem-2;
uint8_t* addrhh = idt_start_mem+7-2;
uint8_t* addrlh = idt_start_mem+1-2;

uint32_t addr = *addrl + (*addrlh<<8) + (*addrh<<16) + (*addrhh<<24);
qhexint(addr);
newline();
uint32_t* address = 0x500;
qhexint(*address);
if(waitforkey() == 0x41){
arbitraryfunc(addr);
}
newline();
qhexint(idt_start_mem);
newline();
qhexint(idtp);	
hang();
}




void idt_init2(){
idt_install();
uint32_t* address = 0x500;
idt_set_gate(0, (*address)+1, 0x08, 0x8e);
qhexint(idt_start_mem);
newline();
qhexint(*address);
// waitforkey();
idt_test();
int j = 1/0;
test();

memdump(idt_start_mem);
}