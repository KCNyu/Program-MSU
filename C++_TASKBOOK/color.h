//color.h
#ifndef COLOR_H
#define COLOR_H

const int F_BLACK = 0x01;   // 000001
const int F_RED = 0x02;	    // 000010
const int F_GREEN = 0x03;   // 000011
const int F_YELLOW = 0x04;  // 000100
const int F_BLUE = 0x05;    // 000101
const int F_PURPLE = 0x06; // 000110
const int F_WHITE = 0x07;   // 000111

const int B_BLACK = 0x08; // 001000
const int B_RED = 0x10;	  // 010000
const int B_GREEN = 0x18; // 011000
const int B_BROWN = 0x80; // 100000
const int B_BLUE = 0x88;  // 101000
const int B_WHITE = 0x90; // 110000
//缺一个111000，但就这些了

bool setColor(int color); // color是一个前景色于一个后景色的位或结果
void resetFColor();	  // 重置前景色
void resetBColor();	  // 重置背景色

#endif // COLOR_H