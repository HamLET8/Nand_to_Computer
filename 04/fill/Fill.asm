// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@SCREEN
D=A
@arr
M=D		//arr = screen

(CHECK)
@i
M = 0 		//int i = 0

@KBD
D = M
@BLACK
D ; JGT		//if(kby > 0) goto BLACK

(WHITE)
@i
D = M
@8096
D = D-A
@CHECK	
D;JEQ 		//if (i  == 8096) goto CHECK

@arr
D = M
@i
A = M+D		
M=0		//M[arr + i] = 0

@i
M=M+1

@WHITE		//goto WHITE
0;JMP


(BLACK)			//display Black
@i
D = M
@8096
D = D-A
@CHECK	
D;JEQ 		//if (i  == 8096) goto CHECK

@arr
D = M
@i
A = M+D
M=-1		//M[arr + i] = -1

@i
M=M+1		//++i

@BLACK
0;JMP