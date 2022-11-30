//pic stuff

//resets the pic status so it can handle more interupts again
void picintdone(unsigned char irq){
if(irq >= 8){
byteout(spiccommand,PIC_EOI);
}
else{
byteout(mpiccommand,PIC_EOI);
}}

void PIC_init(int offset1, int offset2){
unsigned char a1, a2;

a1 = bytein(mpicdata);                        // save masks
a2 = bytein(spicdata);

byteout(mpiccommand, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
wait(2);
byteout(spiccommand, ICW1_INIT | ICW1_ICW4);
wait(2);
byteout(mpicdata, offset1);                 // ICW2: Master PIC vector offset
wait(2);
byteout(spicdata, offset2);                 // ICW2: Slave PIC vector offset
wait(2);
byteout(mpicdata, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
wait(2);
byteout(spicdata, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
wait(2);

byteout(mpicdata, ICW4_8086);
wait(2);
byteout(spicdata, ICW4_8086);
wait(2);

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

void enint(){
__asm__("sti");
}