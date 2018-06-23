#include "color.h"



Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
{
	col[0] = _r;
	col[1] = _g;
	col[2] = _b;
	col[3] = _a;
}

void Color::SetColor(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
{
	col[0] = _r;
	col[1] = _g;
	col[2] = _b;
	col[3] = _a;
}


uint8_t& Color::operator[](size_t n)
{
	return col[n];
}

const uint8_t& Color::operator[](size_t n) const
{
	return col[n];
}