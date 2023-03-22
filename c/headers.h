//defing some video stuff
#define VIDEO_ADDRESS (char*)0xb8000
//these are for text
#define MAX_ROWS 25
#define MAX_COLS 40
// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f
// Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
//for ifdefs for debug checking
#define debug

//includesh
#include <stdint.h>
// #include <string.h>

//testing

//pic controll stuff
#define mpiccommand 0x0020
#define mpicdata 0x0021
#define spiccommand 0x00A0
#define spicdata 0x00A1
#define PIC_EOI	0x20

//pic data codes
#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */


//defining the font
#define ah 0x3F333300
#define al 0x0C1E3333

#define bh 0x66663F00
#define bl 0x3F66663E

#define ch 0x03663C00
#define cl 0x3C660303

#define dh 0x66361F00
#define dl 0x1F366666

#define eh 0x16467F00
#define el 0x7F46161E

#define fh 0x16060F00
#define fl 0x7F46161E

#define gh 0x73667C00
#define gl 0x3C660303

#define hh 0x33333300
#define hl 0x3333333F

#define ih 0x0C0C1E00
#define il 0x1E0C0C0C

#define jh 0x33331E00
#define jl 0x78303030

#define kh 0x36666700
#define kl 0x6766361E

#define lh 0x46667F00
#define ll 0x0F060606

#define mh 0x6B636300
#define ml 0x63777F7F

#define nh 0x73636300
#define nl 0x63676F7B

#define oh 0x63361C00
#define ol 0x1C366363

#define ph 0x06060F00
#define pl 0x3F66663E

#define qh 0x3B1E3800
#define ql 0x1E333333

#define rh 0x36666700
#define rl 0x3F66663E

#define sh 0x38331E00
#define sl 0x1E33070E

#define th 0x0C0C1E00
#define tl 0x3F2D0C0C

#define uh 0x33333F00
#define ul 0x33333333

#define vh 0x331E0C00
#define vl 0x33333333

#define wh 0x7F776300
#define wl 0x6363636B

#define xh 0x1C366300
#define xl 0x6363361C

#define yh 0x0C0C1E00
#define yl 0x3333331E

#define zh 0x4C667F00
#define zl 0x7F633118

#define gth 0x180C0600
#define gtl 0x060C1830

#define h1 0x0C0C3F00
#define l1 0x0C0E0C0C

#define h2 0x06333F00
#define l2 0x1E33301C

#define h3 0x30331E00
#define l3 0x1E33301C

#define h4 0x7F307800
#define l4 0x383C3633

#define h5 0x30331E00
#define l5 0x3F031F30

#define h6 0x33331E00
#define l6 0x1C06031F

#define h7 0x0C0C0C00
#define l7 0x3F333018

#define h8 0x33331E00
#define l8 0x1E33331E

#define h9 0x30180E00
#define l9 0x1E33333E

#define h0 0x6F673E00
#define l0 0x3E63737B

#define hhy 0x00000000
#define lhy 0x0000003F

#define hbs 0x30604000
#define lbs 0x03060C18

#define hes 0x003F0000
#define les 0x00003F00 

#define hsc 0x000C0C06
#define lsc 0x000C0C00

#define tildeh 0x00000000
#define tildel 0x6E3B0000


#define IDTBASE 0x00000000
#define IDTSIZE 2048
#define IDT_MAX_DESCRIPTORS 64

#define idtstart 0x0

#define picw 0


#define true 1
#define false 0


// #define crash

//defing the functions
void prstr(long strstart);
void praddr(long addr);
void idtclear();
void hexdig(int num);
void hexint(int num);
void memdump(int start);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);
void exception_handler(void);
void Qshutdown();
void picinit();
void enint();
void EOI(int pic);
void IRQ_clear_mask(unsigned char IRQline);
void IRQ_set_mask(unsigned char IRQline);
void PIC_init(int offset1, int offset2);
void picintdone(unsigned char irq);
int getcode(int charin, int mode);
void crash();
void setpixel(int x, int y, char colour);
void charpr(int x, int y, int character, char colour);
void crash();
int scancode(int scancodein);
int waitforkey();
int timekey(int time);
void wait(int time);
void printint(int num);
int rand(int min, int max);
int floordiv(int num, int divider);
int checkkey();
int getkey();
void addkey();
int bytein(int port);
int wordin(int port);
void byteout(int port, unsigned char data);
void wordout(int port, unsigned short data);
void corcol();
void newline();
void teleprint1(long a, int colour);
void teleprint2(int colour, long a, long b);
void teleprint3(int colour, long a, long b, long c);
void clear();
void init();
void print_string(int row, int column, int colour, long in);
void teleprint(int row, int column, int colour, long in);
void telechar(int char_to_print, int colour);
int getrow();
int getcol();
void setoffset(int row, int column);
void hang();
int remainder(int num, int divider);
int max(int a, int b);
void scroll();
void print_char(int char_to_print, int colour);
int offset();
void memcpy(char* source, char* dest, int no_bytes);
