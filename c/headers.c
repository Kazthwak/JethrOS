#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f
// Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
#define debug

#include <b8x8font.h>

#define IDTBASE 0x00000000
#define IDTSIZE 0xFF

// #define crash

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
void teleprint1(int colour, long a);
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
