#ifndef FLEW_COLOR_H
#define FLEW_COLOR_H

#include <inttypes.h>

class Color
{
public:

	Color(uint8_t _r = 255, uint8_t _g = 255, uint8_t _b = 255, uint8_t _a = 255);

	void SetColor(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255);

	uint8_t& operator[](size_t n);
	const uint8_t& operator[](size_t n) const;

private:

	//r    g    b    a
	uint8_t col[4];
};





#endif