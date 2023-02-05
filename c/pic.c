//pic stuff
void picinit(){
PIC_init(0x40,0x48);
// idt_init();
}

// void idtclear(){
// for(int i = 0; i < 1024; i++){
// long tmp = i+0x100;
// *(int8_t*)tmp = 0x00;
// }
// }

//resets the pic status so it can handle more interupts again
void picintdone(unsigned char irq){
if(irq >= 8){
byteout(spiccommand,PIC_EOI);
}
else{
byteout(mpiccommand,PIC_EOI);
}}

void PIC_init(int offset1, int offset2){
teleprint(0,0,-1,0x50494320);
unsigned char a1, a2;

a1 = bytein(mpicdata);                        // save masks
a2 = bytein(spicdata);

byteout(mpiccommand, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
wait(picw);
byteout(spiccommand, ICW1_INIT | ICW1_ICW4);
wait(picw);
byteout(mpicdata, offset1);                 // ICW2: Master PIC vector offset
wait(picw);
byteout(spicdata, offset2);                 // ICW2: Slave PIC vector offset
wait(picw);
byteout(mpicdata, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
wait(picw);
byteout(spicdata, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
wait(picw);

byteout(mpicdata, ICW4_8086);
wait(picw);
byteout(spicdata, ICW4_8086);
wait(picw);

byteout(mpicdata, a1);   // restore saved masks.
byteout(spicdata, a2);
}


void IRQ_set_mask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = mpicdata;
    } else {
        port = spicdata;
        IRQline -= 8;
    }
    value = bytein(port) | (1 << IRQline);
    byteout(port, value);        
}

void IRQ_clear_mask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = mpicdata;
    } else {
        port = spicdata;
        IRQline -= 8;
    }
    value = bytein(port) & ~(1 << IRQline);
    byteout(port, value);        
}

void EOI(int pic){
if(pic == 0){
byteout(mpiccommand, 0x20);
}else{
byteout(spiccommand, 0x20);
byteout(mpiccommand, 0x20);
}
}


//setting up idt now. def didnt copy paste the code I am offended you would even think that
// 32bit IDT entry

__attribute__((noreturn))
void exception_handler(){
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
__builtin_unreachable();
}

/*

typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

// create the idt table
// __attribute__((aligned(0x10))) 
// static idt_entry_t idt[256] = 0x0;
 // Create an array of IDT entries; aligned for performance

//idtr structure
typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

//define one of them
static idtr_t idtr;

//the default interupt handler
__attribute__((noreturn))
void exception_handler() {
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

//sets the idt entry "vector" to a giver isr with the given flags
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
int* idtptr = 0;
//defines an idt entry wat the appropriate idt location
    idt_entry_t* descriptor = idtptr[vector];

//sets the low to 0xffff
    descriptor->isr_low        = (uint16_t)((uint32_t)isr) & 0xFFFF;
//sets the kernel offset
    descriptor->kernel_cs      = 0x0; // this value can be whatever offset your kernel code selector is in your GDT
//sets the flags
    descriptor->attributes     = flags;
//
    descriptor->isr_high       = (uint16_t)((uint32_t)isr) >> 16;
//
    descriptor->reserved       = 0;
}

extern void* isr_stub_table[];

void idt_init(){
//print out for debugging
teleprint(0,0,-1,0x49445420);
//set the base to be the location of the IDT we initialized
    idtr.base = (uintptr_t)idtstart;
    idtr.limit = sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        // vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    // __asm__ volatile ("sti"); // set the interrupt flag
}

*/