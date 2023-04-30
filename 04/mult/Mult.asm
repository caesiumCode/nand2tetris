// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// n = 1
// LOOP:
// 	   if (n > R0) goto STOP
// 	   R2 = R2 + R1
//	   n = n + 1
//
// STOP:
//	   goto STOP


	// n = 1
	@n
	M=1
	// Set R2=0
	@R2
	M=0

(LOOP)
	// Compute n - R0
	@n
	D=M
	@R0
	D=D-M 

	// Check if n - R0 > 0
	@STOP
	D;JGT

	// R2 = R2 + R1
	@R1
	D=M
	@R2
	M=D+M

	// n++
	@n
	M=M+1

	@LOOP
	0;JMP

(STOP)
	@STOP
	0;JMP