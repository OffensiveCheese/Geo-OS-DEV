#include "sys.h"

void* memset(void* ptr, int val, size_t size) {
	unsigned char* bufptr = (unsigned char*)ptr;
	for (size_t i = 0; i < size; i++) {
		bufptr[i] = (unsigned char)val;
	}
	return ptr;
}