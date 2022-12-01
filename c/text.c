// #define ca 0x0C1E33333F333300

//prints a character in an 8x8 font to x,y
void charpr(int x, int y, int character, char colour){

int char2pr = getcode(character,1);
for(int i = 0; i < 4; i++){
for(int j =0; j < 8; j++){
// tmp = (a >> b)&1
if((char2pr >> ((i*8+j)))&0x1 == 1){
setpixel(x+j,y+(7-i), colour);
}else{
setpixel(x+j,y+(7-i), 0x0);
}
}
}

char2pr = getcode(character, 2);
for(int i = 0; i < 4; i++){
for(int j =0; j < 8; j++){
// tmp = (a >> b)&1
if((char2pr >> ((i*8+j)))&0x1 == 1){
setpixel(x+j,y+3-i, colour);
}else{
setpixel(x+j,y+3-i, 0x0);
}
}
}

}

//returns the font data. mode defines whether it returns the high or low half of the font
int getcode(int charin, int mode){
//turn uppercase if lowercase
if(charin > 0x60 && charin <= 0x7a){
charin -= 0x20;
}

//return lower half
//al
if(mode == 1){
if(charin == 0x3e){return(gth);}
if(charin == 0x41){return(ah);}
if(charin == 0x42){return(bh);}
if(charin == 0x43){return(ch);}
if(charin == 0x44){return(dh);}
if(charin == 0x45){return(eh);}
if(charin == 0x46){return(fh);}
if(charin == 0x47){return(gh);}
if(charin == 0x48){return(hh);}
if(charin == 0x49){return(ih);}
if(charin == 0x4a){return(jh);}
if(charin == 0x4b){return(kh);}
if(charin == 0x4c){return(lh);}
if(charin == 0x4d){return(mh);}
if(charin == 0x4e){return(nh);}
if(charin == 0x4f){return(oh);}
if(charin == 0x50){return(ph);}
if(charin == 0x51){return(qh);}
if(charin == 0x52){return(rh);}
if(charin == 0x53){return(sh);}
if(charin == 0x54){return(th);}
if(charin == 0x55){return(uh);}
if(charin == 0x56){return(vh);}
if(charin == 0x57){return(wh);}
if(charin == 0x58){return(xh);}
if(charin == 0x59){return(yh);}
if(charin == 0x5a){return(zh);}
if(charin == 0x30){return(h0);}
if(charin == 0x31){return(h1);}
if(charin == 0x32){return(h2);}
if(charin == 0x33){return(h3);}
if(charin == 0x34){return(h4);}
if(charin == 0x35){return(h5);}
if(charin == 0x36){return(h6);}
if(charin == 0x37){return(h7);}
if(charin == 0x38){return(h8);}
if(charin == 0x39){return(h9);}
if(charin == 0x2d){return(hhy);}
if(charin == 0x5c){return(hbs);}
if(charin == 0x3d){return(hes);}
if(charin == 0x3b){return(hsc);}
if(charin == 0x7e){return(tildeh);}
//return upper half
//ah
}else{
if(charin == 0x3e){return(gtl);}
if(charin == 0x41){return(al);}
if(charin == 0x42){return(bl);}
if(charin == 0x43){return(cl);}
if(charin == 0x44){return(dl);}
if(charin == 0x45){return(el);}
if(charin == 0x46){return(fl);}
if(charin == 0x47){return(gl);}
if(charin == 0x48){return(hl);}
if(charin == 0x49){return(il);}
if(charin == 0x4a){return(jl);}
if(charin == 0x4b){return(kl);}
if(charin == 0x4c){return(ll);}
if(charin == 0x4d){return(ml);}
if(charin == 0x4e){return(nl);}
if(charin == 0x4f){return(ol);}
if(charin == 0x50){return(pl);}
if(charin == 0x51){return(ql);}
if(charin == 0x52){return(rl);}
if(charin == 0x53){return(sl);}
if(charin == 0x54){return(tl);}
if(charin == 0x55){return(ul);}
if(charin == 0x56){return(vl);}
if(charin == 0x57){return(wl);}
if(charin == 0x58){return(xl);}
if(charin == 0x59){return(yl);}
if(charin == 0x5a){return(zl);}
if(charin == 0x30){return(l0);}
if(charin == 0x31){return(l1);}
if(charin == 0x32){return(l2);}
if(charin == 0x33){return(l3);}
if(charin == 0x34){return(l4);}
if(charin == 0x35){return(l5);}
if(charin == 0x36){return(l6);}
if(charin == 0x37){return(l7);}
if(charin == 0x38){return(l8);}
if(charin == 0x39){return(l9);}
if(charin == 0x2d){return(lhy);}
if(charin == 0x5c){return(lbs);}
if(charin == 0x3d){return(hes);}
if(charin == 0x3b){return(lsc);}
if(charin == 0x7e){return(tildel);}
}
return(0);
}