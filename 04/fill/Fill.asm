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


// max_index = 8192
// 
// START:
// 	   index = 0
// 	   if (RAM[KBD] == 0) goto WHITE
// 	   goto BLACK
// 
// WHITE:
// 	   color=0
// 	   goto FILL
// BLACK:
// 	   color=-1
// 	   goto FILL
// 
// FILL:
// 	   if (index - max_index >= 0) goto START
// 	   RAM[SCREEN + index] = color
// 	   index = index + 1
// 	   goto FILL

// max_index = 8192
@8192
D=A
@maxi
M=D

(START)
	// index = 0
	@index
	M=0

	@KBD
	D=M
	@WHITE
	D;JEQ

	@BLACK
	0;JMP

(WHITE)
	@color
	M=0
	@FILL
	0;JMP
(BLACK)
	@color
	M=-1
	@FILL
	0;JMP

(FILL)
	@index
	D=M
	@maxi
	D=D-M
	@START
	D;JGE

	// Get ptr = RAM[SCREEN + index]
	@SCREEN
	D=A
	@index
	D=D+M
	@ptr
	M=D
	
	@color
	D=M

	// RAM[SCREEN + index] = color
	@ptr
	A=M
	M=D

	@index
	M=M+1

	@FILL
	0;JMP



