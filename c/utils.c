//hangs forever
void hang(){
while(1==1);
}

//crashes (at least until i set up an interupt to catch divide by 0 errors)
void crash(){int k = 0; int i = 1/k;}

//gets num%divider
int remainder(int num, int divider){
//num = num/divider
// ive simplified the equation to prevent the use of floats
//  prieviously, it crashed the emulator when it got the the line with a float
int tmp = num;
int i = 0;
while(1==1){
// i++;
// if(1==0&&i > 10*divider){crash();return(divider/4);}
if(tmp < divider){
return(tmp);
}
tmp = tmp - divider;
}
}

//gets num/divider ignoring remainders
int floordiv(int num, int divider){
//num = num/divider
// ive simplified the equation to prevent the use of floats
//  prieviously, it crashed the emulator when it got the the line with a float
int tmp = num;
int i = 0;
while(1==1){
if(1==0&&i > 10*divider){crash();return(divider/4);}
if(tmp < divider){
return(i);
}
tmp = tmp - divider;
i++;
}
}

//dumps some bytes after start
void memdump(int start){
clear();
for(int i = 0; i < 25; i++){
for(int j = 0; j < 13; j++){
long tmp = start+((i * 13) + j)+1;
setoffset(i,j*3-1);
hexint(*(int8_t*)tmp);
}
}
}

void hexdig(int num){
int tmp;
tmp = num + 0x30;
if(num > 9){tmp += 0x07;}
telechar(-1,tmp);
}

void hexint(int num){
int tmp = (num >> 4) & 0x0f;
hexdig(tmp);
tmp = num & 0x0f;
hexdig(tmp);
}

//the funtion that initializes amain, if amain returns it prints an error message
void init(){
clear();
setoffset(0,-1);
teleprint(0,0,-1,0x494e4954);
teleprint(0,0,-1, 0x494e4720);
picinit();
amain();
clear();
#ifdef debug
hang();
#endif
}

//clears the screen
void clear(){
for(int i = 0; i < (64000); i++){
char* grp = (char*)(0xa0000-0xf7c)+i;
*(grp+i) = 0;
}for(int i = 0; i < (64000); i++){
char* grp = (char*)(0xb0000-0xf7c)+i;
*(grp+i) = 0;
}
}

//prints the long to the current row and column
//row and column inputs are not used but it breaks if I don't 
void teleprint(int row, int column, int colour, long in){
char tmp;
int j;
tmp = (in >> 24)&0xff;
telechar(colour,tmp);
tmp = (in >> 16)&0xff;
telechar(colour,tmp);
tmp = (in >> 8)&0xff;
telechar(colour,tmp);
tmp = (in >> 0)&0xff;
telechar(colour,tmp);
}

//prints a single character to the current offset
void telechar(int colour, int char_to_print){
inccol();
print_char(char_to_print,colour);
}

//DONOTUSE THE FUNCTIONS
//a wrapper function, prints out the 2 longs one after each other
void teleprint2(int colour, long a, long b){
teleprint(0,0,colour,a);
teleprint(0,0,colour,b);
}

//a wrapper function, prints out the 3 longs one after each other
void teleprint3(int colour, long a, long b, long c){
teleprint1(colour,a);
teleprint1(colour,b);
teleprint1(colour,c);
}

//a wrapper function, prints out the 1 long withour having to give row and column
void teleprint1(long a, int colour){
teleprint(0,0,colour,a);
}

//YOU CAN USE ANY OF THESE
//does newline
void newline(){
setoffset(getrow()+1,-1);
}

// checks if the column is less than -a, setting it to -1 if it is
void corcol(){
if(getcol() < -1){
setoffset(getrow(),-1);
}
}

//prints an integer up to 999
//if the number is bigger, it does strange things
void printint(int num){
int tmp;
//100s
tmp = floordiv(num,100);
tmp += 0x30;
telechar(-1,tmp);
//10s
tmp = floordiv(remainder(num,100),10);
tmp += 0x30;
telechar(-1,tmp);
//1s
tmp = remainder(num,10);
tmp += 0x30;
telechar(-1,tmp);
}

//return the larger of the two number, currently unused
int max(int a, int b){
if(a > b){
return(a);
}else{
return(b);
}
}

//waits for time
void wait(int time){
for(int i = 0; i < time*2000000; i++){}
}

//gets a random number, can be quite slow
int rand(int min, int max){
int* seed = (int*)0x7c0a;
*seed = *seed * 949;
*seed = *seed + 2169;
int tmp = *seed; 
*seed = remainder(*seed, 3929);
int tmpmax = max-min;
/*
int out = remainder(tmp,tmpmax);
// crash();
out += min;
return(out); 
*/
return(min+remainder(tmp,tmpmax));
}


// calculates the video memory offset from the row and column  now obsolete
int offset(){
int row = getrow();
int column = getcol();
int tmp;
//adds on the offset for the row that is given
tmp = MAX_COLS * row;
//adds on the offset for the column
tmp += column + 1;
//multiply it by 2 because each character is 2 bytes (one for ascii code and one for the colour code)
tmp *= 2;
return tmp;
}

// copies the memory from source to destination
void memcpy(char* source, char* dest, int no_bytes){
for(int i = 0; i<no_bytes;i++){
*(dest + i) = *(source +i);
}
}
