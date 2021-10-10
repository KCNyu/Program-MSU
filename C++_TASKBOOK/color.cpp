//color.cpp
#include "color.h"
#include <iostream>

bool setColor(int color)
{
	bool ret = true;
	int fore = color % 8;	    //取color的后3位
	int back = (color / 8) * 8; //将color的后3位清空 (即取前3位)
	switch (fore)
	{
	case F_BLACK:
		std::cout << "\033[30m";
		break;
	case F_RED:
		std::cout << "\033[31m";
		break;
	case F_GREEN:
		std::cout << "\033[32m";
		break;
	case F_YELLOW:
		std::cout << "\033[33m";
		break;
	case F_BLUE:
		std::cout << "\033[34m";
		break;
	case F_PURPLE:
		std::cout << "\033[35m";
		break;
	case F_WHITE:
		std::cout << "\033[37m";
		break;
	default:
		ret = false;
	}
	switch (back)
	{
	case B_BLACK:
		std::cout << "\033[40m";
		break;
	case B_RED:
		std::cout << "\033[41m";
		break;
	case B_GREEN:
		std::cout << "\033[42m";
		break;
	case B_BROWN:
		std::cout << "\033[43m";
		break;
	case B_BLUE:
		std::cout << "\033[44m";
		break;
	case B_WHITE:
		std::cout << "\033[47m";
		break;
	default:
		ret = false;
	}
	return ret;
}
void resetFColor()
{
	std::cout << "\033[39m";
}
void resetBColor()
{
	std::cout << "\033[49m";
}