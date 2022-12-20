//main is what is called, but all it does is call init() which calls amain
void main(){
setoffset(0,-1);
teleprint1(-1,0x4c4f4144);
teleprint1(-1,0x4544204b);
teleprint1(-1,0x45524e45);
teleprint1(-1,0x4c202020);
init();
}


//amain stands for actual main, and is where the kernel should be put
void amain(){
memdump(0x200);
hang();
// hang();
// teleprint3(-1, 0x54484953, 0x49533132, 0x43484152);
// hang();
for(int i = 0x2d; i < 255; i++){
telechar(-1,i);
wait(1);
if(i == 0x60){
hang();
}
}
hang();
}


/*
20 	00100000 	&#32; 	space 	Space
21 	00100001 	&#33; 	! 	Exclamation mark
22 	00100010 	&#34; 	" 	Double quote
23 	00100011 	&#35; 	# 	Number
24 	00100100 	&#36; 	$ 	Dollar sign
25 	00100101 	&#37; 	% 	Percent
26 	00100110 	&#38; 	& 	Ampersand
27 	00100111 	&#39; 	' 	Single quote
28 	00101000 	&#40; 	( 	Left parenthesis
29 	00101001 	&#41; 	) 	Right parenthesis
2A 	00101010 	&#42; 	* 	Asterisk
2B 	00101011 	&#43; 	+ 	Plus
2C 	00101100 	&#44; 	, 	Comma
2D 	00101101 	&#45; 	- 	Minus
2E 	00101110 	&#46; 	. 	Period
2F 	00101111 	&#47; 	/ 	Slash
30 	00110000 	&#48; 	0 	Zero
31 	00110001 	&#49; 	1 	One
32 	00110010 	&#50; 	2 	Two
33 	00110011 	&#51; 	3 	Three
34 	00110100 	&#52; 	4 	Four
35 	00110101 	&#53; 	5 	Five
36 	00110110 	&#54; 	6 	Six
37 	00110111 	&#55; 	7 	Seven
38 	00111000 	&#56; 	8 	Eight
39 	00111001 	&#57; 	9 	Nine
3A 	00111010 	&#58; 	: 	Colon
3B 	00111011 	&#59; 	; 	Semicolon
3C 	00111100 	&#60; 	< 	Less than
3D 	00111101 	&#61; 	= 	Equality sign
3E 	00111110 	&#62; 	> 	Greater than
3F 	00111111 	&#63; 	? 	Question mark
40 	01000000 	&#64; 	@ 	At sign
41 	01000001 	&#65; 	A 	Capital A
42 	01000010 	&#66; 	B 	Capital B
43 	01000011 	&#67; 	C 	Capital C
44 	01000100 	&#68; 	D 	Capital D
45 	01000101 	&#69; 	E 	Capital E
46 	01000110 	&#70; 	F 	Capital F
47 	01000111 	&#71; 	G 	Capital G
48 	01001000 	&#72; 	H 	Capital H
49 	01001001 	&#73; 	I 	Capital I
4A 	01001010 	&#74; 	J 	Capital J
4B 	01001011 	&#75; 	K 	Capital K
4C 	01001100 	&#76; 	L 	Capital L
4D 	01001101 	&#77; 	M 	Capital M
4E 	01001110 	&#78; 	N 	Capital N
4F 	01001111 	&#79; 	O 	Capital O
50 	01010000 	&#80; 	P 	Capital P
51 	01010001 	&#81; 	Q 	Capital Q
52 	01010010 	&#82; 	R 	Capital R
53 	01010011 	&#83; 	S 	Capital S
54 	01010100 	&#84; 	T 	Capital T
55 	01010101 	&#85; 	U 	Capital U
56 	01010110 	&#86; 	V 	Capital V
57 	01010111 	&#87; 	W 	Capital W
58 	01011000 	&#88; 	X 	Capital X
59 	01011001 	&#89; 	Y 	Capital Y
5A 	01011010 	&#90; 	Z 	Capital Z
5B 	01011011 	&#91; 	[ 	Left square bracket
5C 	01011100 	&#92; 	\ 	Backslash
5D 	01011101 	&#93; 	] 	Right square bracket
5E 	01011110 	&#94; 	^ 	Caret / circumflex
5F 	01011111 	&#95; 	_ 	Underscore
60 	01100000 	&#96; 	` 	Grave / accent
61 	01100001 	&#97; 	a 	Small a
62 	01100010 	&#98; 	b 	Small b
63 	01100011 	&#99; 	c 	Small c
64 	01100100 	&#100; 	d 	Small d
65 	01100101 	&#101; 	e 	Small e
66 	01100110 	&#102; 	f 	Small f
67 	01100111 	&#103; 	g 	Small g
68 	01101000 	&#104; 	h 	Small h
69 	01101001 	&#105; 	i 	Small i
6A 	01101010 	&#106; 	j 	Small j
6B 	01101011 	&#107; 	k 	Small k
6C 	01101100 	&#108; 	l 	Small l
6D 	01101101 	&#109; 	m 	Small m
6E 	01101110 	&#110; 	n 	Small n
6F 	01101111 	&#111; 	o 	Small o
70 	01110000 	&#112; 	p 	Small p
71 	01110001 	&#113; 	q 	Small q
72 	01110010 	&#114; 	r 	Small r
73 	01110011 	&#115; 	s 	Small s
74 	01110100 	&#116; 	t 	Small t
75 	01110101 	&#117; 	u 	Small u
76 	01110110 	&#118; 	v 	Small v
77 	01110111 	&#119; 	w 	Small w
78 	01111000 	&#120; 	x 	Small x
79 	01111001 	&#121; 	y 	Small y
7A 	01111010 	&#122; 	z 	Small z
7B 	01111011 	&#123; 	{ 	Left curly bracket
7C 	01111100 	&#124; 	| 	Vertical bar
7D 	01111101 	&#125; 	} 	Right curly bracket
7E 	01111110 	&#126; 	~ 	Tilde
7F 	01111111 	&#127; 	DEL 	Delete SPEXIAL, USED AS \n
*/