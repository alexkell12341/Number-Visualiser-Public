#pragma once
#include <cstdint>

struct Block {

	enum {
		transparent = 0,
		white,
		black
	};

	std::uint8_t type = 0;
};