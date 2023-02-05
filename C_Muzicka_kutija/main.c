/*
 * C_Muzicka_kutija.c
 *
 * Created: 3.12.2022. 18:05:22
 * Author : Aleksandar Bogdanovic
 */ 

/*
 * Arduino Electronic Piano Keyboard.c
 *
 * Created: 30.11.2022. 17:12:40
 * Author : Aleksandar Bogdanovic
 */ 

// Fast PWM Mode

// All defines
#define F_CPU 16000000							// 16MHz
#define __DELAY_BACKWARD_COMPATIBLE__
#define DEBOUNCE 250							// 250ms

// All includes
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

// Variables
int		tempo;
double	length;

// Notes
#define c3 (16000000 / 256) / 130.81 - 1		// Do3
#define cs3 (16000000 / 256) / 138.59 - 1		// Do3#
#define d3 (16000000 / 256) / 146.83 - 1		// Re3
#define ds3 (16000000 / 256) / 155.56 - 1		// Re3#
#define e3 (16000000 / 256) / 164.81 - 1		// Mi3
#define f3 (16000000 / 256) / 174.61 - 1		// Fa3
#define fs3 (16000000 / 256) / 185.00 - 1		// Fa3#
#define g3 (16000000 / 256) / 196.00 - 1		// Sol3
#define gs3 (16000000 / 256) / 207.65 - 1		// Sol3#
#define a3 (16000000 / 256) / 220.00 - 1		// La3
#define as3 (16000000 / 256) / 233.08 - 1		// La3#
#define b3 (16000000 / 256) / 246.94 - 1		// Si3
//----------------------------------------------------
#define c4 (16000000 / 256) / 261.63 - 1		// Do4
#define cs4 (16000000 / 256) / 277.18 - 1		// Do4#
#define d4 (16000000 / 256) / 293.66 - 1		// Re4
#define ds4 (16000000 / 256) / 311.13 - 1		// Re4#
#define e4 (16000000 / 256) / 329.63 - 1		// Mi4
#define f4 (16000000 / 256) / 349.23 - 1		// Fa4
#define fs4 (16000000 / 256) / 369.99 - 1		// Fa4#
#define g4 (16000000 / 256) / 392.00 - 1		// Sol4
#define gs4 (16000000 / 256) / 415.30 - 1		// Sol4#
#define a4 (16000000 / 256) / 440 - 1			// La4
#define as4 (16000000 / 256) / 466.16 - 1		// La4#
#define b4 (16000000 / 256) / 493.88 - 1		// Si4
//----------------------------------------------------
#define c5 (16000000 / 256) / 523.25 - 1		// Do5
#define cs5 (16000000 / 256) / 554.37 - 1		// Do5#
#define d5 (16000000 / 256) / 587.33 - 1		// Re5
#define ds5 (16000000 / 256) / 622.25 - 1		// Re5#
#define e5 (16000000 / 256) / 659.25 - 1		// Mi5
#define f5 (16000000 / 256) / 698.46 - 1		// Fa5
#define fs5 (16000000 / 256) / 739.99 - 1		// Fa5#
#define g5 (16000000 / 256) / 783.99 - 1		// Sol5
#define gs5 (16000000 / 256) / 830.61 - 1		// Sol5#
#define a5 (16000000 / 256) / 880.00 - 1		// la5
#define as5 (16000000 / 256) / 932.33 - 1		// La5#
#define h5 (16000000 / 256) / 987.77 - 1		// Si5
//----------------------------------------------------

// Note length
#define whole		1
#define half		0.5
#define quarter		0.25
#define eight		0.125
#define sixteenth	0.0625
#define halfdot		0.75
#define quarterdot	0.375
//----------------------------------------------------

// Sound function
void soundOn(double tone, double len) {
	
	DDRD   |= (1 << PORTD5);
	TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << WGM02) | (1 << CS02);
	OCR0A = tone;
	OCR0B = tone / 2;
	
	length = (60.0/tempo)*len*4*1000.0;
	_delay_ms(length);
	DDRD &= (0 << PORTD5);
	_delay_ms(10);
}

// Pause/mute function
void pause(double len) {
	DDRD &= (0 << PORTD5);
	length = (60.0/tempo)*len*1000.0;
	_delay_ms(length);
}
//**********************************************************

// Main	
int main(void) {	
	
    while (1) {
		// Interstellar Main Theme
	/*	tempo = 86;
		soundOn(a4, quarter);
		soundOn(e5, half);
		soundOn(a4, quarter);
		soundOn(e5, half);
		
		soundOn(b4, quarter);
		soundOn(e5, half);
		soundOn(b4, quarter);
		soundOn(e5, half);
		
		soundOn(c5, quarter);
		soundOn(e5, half);
		soundOn(c5, quarter);
		soundOn(e5, half);
		
		soundOn(d5, quarter);
		soundOn(e5, half);
		soundOn(d5, quarter);
		soundOn(e5, half);
		//*******************
		soundOn(a4, quarter);
		soundOn(e5, half);
		soundOn(a4, quarter);
		soundOn(e5, half);
		
		soundOn(b4, quarter);
		soundOn(e5, half);
		soundOn(b4, quarter);
		soundOn(e5, half);
		
		soundOn(c5, quarter);
		soundOn(e5, half);
		soundOn(c5, quarter);
		soundOn(e5, half);
		
		soundOn(d5, quarter);
		soundOn(e5, half);
		soundOn(d5, quarter);
		soundOn(e5, half);
		//*******************
		soundOn(a4, quarter);
		soundOn(e5, half);
		soundOn(a4, quarter);
		soundOn(e5, half);
		
		soundOn(b4, quarter);
		soundOn(e5, half);
		soundOn(b4, quarter);
		soundOn(e5, half);
		
		soundOn(c5, quarter);
		soundOn(e5, half);
		soundOn(c5, quarter);
		soundOn(e5, half);
		
		soundOn(d5, quarter);
		soundOn(e5, half);
		soundOn(d5, quarter);
		soundOn(e5, half);
		//*******************
		soundOn(a4, quarter);
		soundOn(e5, half);
		soundOn(a4, quarter);
		soundOn(e5, half);
		
		soundOn(b4, quarter);
		soundOn(e5, half);
		soundOn(b4, quarter);
		soundOn(e5, half);
		
		soundOn(c5, quarter);
		soundOn(e5, half);
		soundOn(c5, quarter);
		soundOn(e5, half);
		
		soundOn(d5, quarter);
		soundOn(e5, half);
		soundOn(d5, quarter);
		soundOn(e5, half);
		
		pause(whole+whole);*/
//**********************************
//		The end of a song
//**********************************		
		
		
		// Linkin Park - Numb
		tempo = 100;
		
		pause(whole);
		pause(eight);
		soundOn(cs5, eight);
		soundOn(e5,	 eight);
		soundOn(cs5, eight);
		soundOn(fs5, quarter+eight);
		soundOn(a5,  quarter+eight);
		soundOn(gs5, half+quarter);
		
		pause(eight);
		soundOn(cs5, eight);
		soundOn(e5,	 eight);
		soundOn(cs5, eight);
		soundOn(a5,  quarter+eight);
		soundOn(gs5, quarter+eight);
		soundOn(e5,  half+quarter);
		
		pause(eight);
		soundOn(cs5, eight);
		soundOn(e5,	 eight);
		soundOn(cs5, eight);
		soundOn(fs5, quarter+eight);
		soundOn(a5,  quarter+eight);
		soundOn(gs5, half+quarter);
		
		pause(eight);
		soundOn(cs5, eight);
		soundOn(e5,	 eight);
		soundOn(cs5, eight);
		soundOn(a5,  quarter+eight);
		soundOn(gs5, quarter+eight);
		soundOn(e5,  half+quarter);
//**********************************
		
		pause(eight);
		soundOn(fs4, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(d5, eight);
		soundOn(cs5, eight+eight);
		soundOn(cs5, eight);
		soundOn(b4, eight);
		soundOn(a4, quarter+eight);
		
		pause(quarter);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(a4, eight);
		soundOn(b4, quarter);
		soundOn(a4, quarter);
		soundOn(e4, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(a4, eight);
		soundOn(b4, quarter);
		soundOn(a4, quarter+eight);
		
		pause(quarter);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(d5, eight);
		soundOn(cs5, eight+eight);
		soundOn(cs5, eight);
		soundOn(b4, eight);
		soundOn(a4, quarter+eight);
		
		pause(eight);
		soundOn(a4, eight);
		soundOn(cs5, eight);
		soundOn(cs5, eight);
		soundOn(b4, eight);
		soundOn(a4, quarter);
		soundOn(b4, quarter);
		soundOn(e4, eight);
		soundOn(cs5, eight);
		soundOn(b4, quarter);
		soundOn(a4, quarter);
		soundOn(b4, quarter);
		soundOn(b4, eight);
		soundOn(cs5, whole);
//**********************************
//		The end of a song
//**********************************
		
		pause(whole+whole+whole);
	}
		return(0);
}




