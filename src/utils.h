#pragma once

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <vector>

void hexdump(void *ptr, int buflen);
void hexdump_vector(std::vector<uint8_t> data);
