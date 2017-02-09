#include "sys.h"

const char* command;

int strcmp(const char* a, const char* b) {
	while(*a && *b && *a == *b) {
		++a; ++b;
	}
	return *a - *b;
}

const char* run(const char* com) {
	if (strcmp(com, "help") == 0) {
		writes("\nGeo OS v1.0\n", 0, 15);
		com = "";
		return com;
	} else {
		writes("\nUnknown command '", 0, 15);
		writes(command, 0, 15);
		writes("'", 0, 15);
		newline();
		com = "";
		return com;
	}
}

unsigned char keyboard_map[] =
{
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',
	'=', '\b', 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
	'p', '[', ']', 0xD4, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k',
	'l', 0, 0, 0, 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm',
	',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Meh i'll just pad this out with a bunch of zeroes. I don't need any released keys.
};

const char* append(unsigned char character, const char* string) {
	size_t stringlen = strlen(string);
	char* string_t = (char*)string;
	string_t[stringlen] = character;
	string_t[stringlen+1] = '\0';
	const char* string_r = (const char*)string_t;
	return string_r;
}

void kb_handler(void) {
	unsigned char scancode = inb(0x60);
	unsigned char key = keyboard_map[scancode];
	if (key == 0xD4) {
		command = run(command);
		return;
	}
	if (scancode & 0x80) {
		// I don't have a use for the alt, control or shift keys yet.
	} else {
		command = append(key, command);
		writec(key, 0, 15);
	}
}