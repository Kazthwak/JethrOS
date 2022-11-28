//supposed to handle scrolling but not implemented yet
void scroll(){
}

void charpr(int x, int y, int character, char colour){

char fontchar[8];
switch(character){
case 0x41:
char fontchar[8] = {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00};
goto fontset;
}
fontset:
/*
for(*ip = 0; *ip < 8; *ip++){
for(*jp = 0; *jp < 8; *jp++){
if((fontchar[*ip] >> *jp) & 1){
setpixel(x+*jp,y+*ip,0xf);
}else{
setpixel(x+*jp,y+*ip,0x5);
}
}
}*/
int i;
int j;
while(1){
if(i >= 8){break;}
while(1){
if(j >= 8){break;}
if((fontchar[i] >> j) & 1){
setpixel(x+j,y+i,0xf);
}else{
setpixel(x+j,y+i,0x5);
}
j++;
}
i++;
}
}

void setpixel(int x, int y, char colour){
int poff = (320*y)+x;
if(poff > 64000){
poff -= 64000;
char* grp = (char*)0xb0000;
grp += poff;
*grp = (char)colour;
}else{
char* grp = (char*)0xa0000;
grp += poff;
*grp = colour;
}
}

//prints a char to row and column with the colour specified 
void print_char(int char_to_print, int colour){
int going = 1;
while(going == 1){
// if the colour is 0, sets it to the default value of white on black
if(colour == 0){
colour = WHITE_ON_BLACK;
}
//sets the location to print to
char* loc = (char*)VIDEO_ADDRESS;
//offset the location to be the correct row and column using the function
loc += offset();
//writes the ascii code to the location
*loc = char_to_print;
//prints the colour code to the next byte
loc += 1;
*loc = colour;
break;
}
}

void print_string(int row, int column, int colour, long in){
setoffset(row,column);
long* ad = (long*)0x7c01;
*ad = in;
int length = 4;
//I KNOW THAT YOU CAN WRITE MORE THAN 1 BYTE TO AN INT TO MAKE STRING
//MAKE FUNCTION WORK AND: (SINCE THIS IS HOW THEY FORMAT)
//PULL THEM IN REVERSE ORDER
int tmpcolumn = column;
int* chars = (int*)0x7c00;
for(int i = 0; i < length; i++){
setoffset(row,column+i);
chars = (int*)0x7c00+length-i;
print_char(*chars,0);
}
}

void setoffset(int row, int column){
int offsett = offset();
offsett /= 2;
int* rowloc = (int*)0x7c05;
int* colloc = (int*)0x7c10;
*rowloc = row;
*colloc = column;
}

void inccol(){
setoffset(getrow(),getcol()+1);
if(getcol() >= MAX_COLS){
setoffset(getrow()+1,-1);
}
corcol();
}

int getrow(){
int* rowloc = (int*)0x7c05;
return(*rowloc);
}

int getcol(){
int* colloc = (int*)0x7c10;
return(*colloc);
}

// KEYBOARD

int getkey(){

}

int checkkey(){

}

void addkey(){

}

int timekey(int time){
int tmp = bytein(0x60);
for(int i = 0; i < 1000000*time && bytein(0x60) == tmp; i++){}
if(tmp == bytein(0x60)){return(0);}
else{return(scancode(bytein(0x60)));}
}

int waitforkey(){
int tmp = bytein(0x60);
while(bytein(0x60) == tmp){}
tmp = bytein(0x60);
return(scancode(bytein(0x60)));
}

#define notdone

int scancode(int scancodein){
#ifdef notdone
return(0x41);
#endif
switch(scancodein){
case 0:
return(1);
}
}

int bytein(int port){
unsigned char result;
__asm__("push %ax\n\t"
"push %dx\n\t");
__asm__("in %% dx , %% al" : "=a" (result):"d"((unsigned short)port));
__asm__("pop %dx\n\t"
"pop %ax\n\t");
return((unsigned short)result);
}

void byteout(int port, unsigned char data){
// " a " ( data ) means : load EAX with data
// " d " ( port ) means : load EDX with port
__asm__("out %% al, %% dx" : : "a" (data), "d" ((unsigned short)port));
}

int wordin(int port){
unsigned short result;
__asm__("in %% dx , %% ax" : "=a" (result) : "d" ((unsigned short)port));
return result;
}

void wordout(int port, unsigned short data){
__asm__("out %% ax , %% dx" : : "a" (data), "d" ((unsigned short)port));
}
