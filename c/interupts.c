// #define ca 0x0C1E33333F333300
#define ah 0x3F333300
#define al 0x0C1E3333

void charpr(int x, int y, int character, char colour){

int char2pr = getcode(character,1);
for(int i = 0; i < 4; i++){
for(int j =0; j < 8; j++){
// tmp = (a >> b)&1
if((char2pr >> (31 - (i*8+j)))&0x1 == 1){
setpixel(x+j,y+i, 0x0f);
}else{
setpixel(x+j,y+i, 0x0);
}
}
}

char2pr = getcode(character, 0);
for(int i = 0; i < 4; i++){
for(int j =0; j < 8; j++){
// tmp = (a >> b)&1
if((char2pr >> (31 - (i*8+j)))&0x1 == 1){
setpixel(x+j,y+i+4, 0x0f);
}else{
setpixel(x+j,y+i+4, 0x0);
}
}
}

}

int getcode(int charin, int mode){
//return lower half
if(mode == 1){
return(al);
}
//return upper half
else{
return(ah);
}
}