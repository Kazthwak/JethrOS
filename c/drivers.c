//supposed to handle scrolling but not implemented yet
void scroll(){
}

//sets the pixel at x, y to colour
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

//prints a char to the current offset with the colour specified 
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

//prints the four chars stored in the long in to row, column
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

//sets the teleprinting location
void setoffset(int row, int column){
int offsett = offset();
offsett /= 2;
int* rowloc = (int*)0x7c05;
int* colloc = (int*)0x7c10;
*rowloc = row;
*colloc = column;
}

//increments the row so it goes to the next character
void inccol(){
setoffset(getrow(),getcol()+1);
if(getcol() >= MAX_COLS){
setoffset(getrow()+1,-1);
}
corcol();
}

//gets the current row
int getrow(){
int* rowloc = (int*)0x7c05;
return(*rowloc);
}

//gets the current column
int getcol(){
int* colloc = (int*)0x7c10;
return(*colloc);
}

// KEYBOARD

//gets the first key in the buffer
int getkey(){

}

//checks if there is a key in the buffer
int checkkey(){

}

//adds a key to the buffer
void addkey(){

}

//TIMEKEY AND WAITFORKEY are rubbish and do not use interupt keyboard drivers
//tries for time to get a key, returns 0 if none are given
int timekey(int time){
int tmp = bytein(0x60);
for(int i = 0; i < 1000000*time && bytein(0x60) == tmp; i++){}
if(tmp == bytein(0x60)){return(0);}
else{return(scancode(bytein(0x60)));}
}

//waits for key
int waitforkey(){
int tmp = bytein(0x60);
while(bytein(0x60) == tmp){}
tmp = bytein(0x60);
return(scancode(bytein(0x60)));
}

#define notdone

//returns the char code of the scancode given
int scancode(int scancodein){
#ifdef notdone
return(0x41);
#endif
switch(scancodein){
case 0:
return(1);
}
}

//takes a byte from port
int bytein(int port){
unsigned char result;
__asm__("push %ax\n\t"
"push %dx\n\t");
__asm__("in %% dx , %% al" : "=a" (result):"d"((unsigned short)port));
__asm__("pop %dx\n\t"
"pop %ax\n\t");
return((unsigned short)result);
}

//gives a byte to port
void byteout(int port, unsigned char data){
// " a " ( data ) means : load EAX with data
// " d " ( port ) means : load EDX with port
__asm__("out %% al, %% dx" : : "a" (data), "d" ((unsigned short)port));
}

// takes a word from port
int wordin(int port){
unsigned short result;
__asm__("in %% dx , %% ax" : "=a" (result) : "d" ((unsigned short)port));
return result;
}

//gives a word to port
void wordout(int port, unsigned short data){
__asm__("out %% ax , %% dx" : : "a" (data), "d" ((unsigned short)port));
}