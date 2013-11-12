/*
 * StringInvert.asm
 *
 *  Created: 2013-11-12 17:22:02
 *   Author: Mateusz
 */ 
	//Inicjalizacja stosu
	LDI R16,low(RAMEND)
	OUT	SPL,R16
	LDI R16,high(RAMEND)	
	OUT SPH, R16

	//Miejsce w kt�rym odwr�cony napis b�dzie przechowywany
	LDI XL, 0x00
	LDI XH, 0x01
	//Miejsce w pami�ci flash w kt�rym napis jest zapisany
	LDI ZL, low(2 * NAPIS)
	LDI ZH, high(2 * NAPIS)

	.def tmp = R17
	LDI tmp, 0x00
	
	// Zachowanie stanu rejestr�w na stosie
	PUSH XL
	PUSH XH
	PUSH ZL
	PUSH ZH
	//Wrzuceni pomocniczego 0
	PUSH tmp
	
	//Wrzucanie na stos kolejnych liter slowa, a� do otrzymania 0
	INVERT:
	LPM tmp, Z+ 
	CPI tmp, 0
	BREQ COPY
	PUSH tmp
	JMP INVERT

	//�ci�ganie kolejnych liter s�owa, a� do otrzymania 0, kt�re by�o wrzucone jako pomocnicze przed p�tl� INVERT
	COPY:
	POP tmp
	CPI tmp, 0
	BREQ END
	ST X+, tmp
	JMP COPY

	END:
	//Odzyskanie stanu rejestr�w
	POP ZH
	POP ZL
	POP XH
	POP XL

	//Zapis do pami�ci flash napisu
	.CSEG
	.org FLASHEND - 0x100

	NAPIS: .db "Napis",0
