void hang(){
while(1==1);
}

void crash(){int i = 1/0;}

int remainder(int num, int divider){
//num = num/divider
// ive simplified the equation to prevent the use of floats
//  prieviously, it crashed the emulator when it got the the line with a float
int floor = num/divider;
return(num-(divider*floor));
}

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

void init(){
clear();
amain();
clear();
teleprint2(0,0x4552524f, 0x52000000);
#ifdef debug
hang();
#endif
}

void clear(){
for(int i = 0; i < (64000); i++){
char* grp = (char*)(0xa0000-0xf7c)+i;
*(grp+i) = 0;
}for(int i = 0; i < (64000); i++){
char* grp = (char*)(0xb0000-0xf7c)+i;
*(grp+i) = 0;
}
}

void teleprint(int row, int column, int colour, long in){
inccol();
print_string(getrow(),getcol(),colour,in);
}

void telechar(int colour, int char_to_print){
inccol();
print_char(char_to_print,colour);
}

void teleprint2(int colour, long a, long b){
teleprint(0,0,colour,a);
teleprint(0,0,colour,b);
}

void teleprint3(int colour, long a, long b, long c){
teleprint1(colour,a);
teleprint1(colour,b);
teleprint1(colour,c);
}

void teleprint1(int colour, long a){
teleprint(0,0,colour,a);
}

void newline(){
setoffset(getrow()+1,-2);
}

void corcol(){
if(getcol() < 0){
setoffset(getrow(),0);
}
}

void printint(int num){
if(num > 99){
int tmp;
tmp = floordiv(num, 100);
telechar(0,tmp+0x30);
num = remainder(num,100);
if(num < 10){telechar(0,0x30);}
}
if(num > 9){
int tmp;
tmp = floordiv(num, 10);
telechar(0,tmp+0x30);
}
while(num > 9){
num -= 10;
}
telechar(0,num +0x30);
}

//return the larger of the two number, currently unused
int max(int a, int b){
if(a > b){
return(a);
}else{
return(b);
}
}


void wait(int time){
for(int i = 0; i < time*2000000; i++){}
}

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


// calculates the video memory offset from the row and column
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
