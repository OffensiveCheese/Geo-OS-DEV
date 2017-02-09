#include "sys.h"


// We'll want to define some variables.

int x = 0;
int y = 0;
uint16_t *videoptr = (uint16_t *)0xB8000;

// Then, define our functions.

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}


void update_videoptr(void) {
	videoptr = (uint16_t *)0xB8000 + (y * 80 + x);
}

void newline(void) {
	x = 0;
	y++;
	update_videoptr();
}

void backspace(void) {
	if (x == 0 && y == 0) {
		x = 80;
		y = 25;
		update_videoptr();
		return;
	}
	if (x > 0) {
			x--;
			update_videoptr();
			return;
		}
	if (x == 0) {
		y--;
		x = 79;
		update_videoptr();
		return;
	}
	return;
}

void restrictions_tty(void) {
	if (x == 80) {
		if (y == 25) {
			x = 0;
			y = 0;
			update_videoptr();
		}
	}
}

void writec(char c, uint8_t bc, uint8_t fc) {
	restrictions_tty(); // Apply restrictions.
	if (c == '\n') {
		newline();
		return;
	}
	if (c == '\b') {
		backspace();
		*videoptr = ' ' | (((0 << 4) | (0 & 0x0F)) << 8);
		return;
	}
	uint16_t attribute = (bc << 4) | (fc & 0x0F);
	*videoptr = c | (attribute << 8);
	if (x == 80) {
		newline();
		x = 1;
		update_videoptr();
	} else {
		x++;
		update_videoptr();
	}
}

void writes(const char* c, uint8_t bc, uint8_t fc) {
	for (size_t i = 0; i < strlen(c); i++) {
		writec(c[i], bc, fc);
	}
}

void terminal_cls(void) {
	x = 0;
	y = 0;
	update_videoptr();
	for (int i = 0; i < 25; i++) {
		for (int a = 0; a < 80; a++) {
			writec(' ', 0, 0);
		}
	}
}

void terminal_init(void) {
	terminal_cls();
	x = 0;
	y = 0;
	update_videoptr();
}