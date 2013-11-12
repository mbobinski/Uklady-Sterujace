/*
 * StringInvert.asm
 *
 *  Created: 2013-11-12 17:22:02
 *   Author: Mateusz
 */ 
	// Inicjalizacja stosu
	LDI R16,low(RAMEND)
	OUT	SPL,R16
	LDI R16,high(RAMEND)	
	OUT SPH, R16

	// Miejsce w ktorym odwrocony napis bedzie przechowywany
	LDI XL, 0x00
	LDI XH, 0x01
	// Miejsce w pamieci flash w ktorym napis jest zapisany
	LDI ZL, low(2 * NAPIS)
	LDI ZH, high(2 * NAPIS)

	.def tmp = R17
	LDI tmp, 0x00
	
	// Zachowanie stanu rejestrow na stosie
	PUSH XL
	PUSH XH
	PUSH ZL
	PUSH ZH
	// Wrzucenie na stos pomocniczego 0
	PUSH tmp
	
	// Wrzucenie na stos kolejnych liter slowa, az do otrzymania 0
	INVERT:
	LPM tmp, Z+ 
	CPI tmp, 0
	BREQ COPY
	PUSH tmp
	JMP INVERT

	// Sciaganie kolejnych liter slowa, az do otrzymania 0, ktore bylo wrzucone jako pomocnicze przed petla INVERT
	COPY:
	POP tmp
	CPI tmp, 0
	BREQ END
	ST X+, tmp
	JMP COPY

	END:
	// Odzyskanie stanu rejestrow
	POP ZH
	POP ZL
	POP XH
	POP XL

	//Zapis do pamieci flash napisu
	.CSEG
	.org FLASHEND - 0x100

	NAPIS: .db "Napis",0
