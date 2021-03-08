// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R2
M = 0		//R2 = 0

@R0
D = M
@a
M = D;		//a = R0

@R1
D = M
@b
M = D;		//a = R1

(LOOP)
@END
D; JEQ 		//if b==0, goto END

@a
D=M
@R2
M = D+M	//sum = sum + a

@b
M = M-1
D=M

@LOOP
0; JMP

(END)
@END
0;JMP