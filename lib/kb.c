#include "sys.h"

const char* command;

int strcmp(const char* a, const char* b) {
	while(*a && *b && *a == *b) {
		++a; ++b;
	}
	return *a - *b;
}

const char* zero_string(const char* string) {
	char* str = (char *)string;
	for (size_t i = strlen(string); i <= strlen(string); i--) {
		str[i] = '\0';
	}
	const char* ret = (const char*)str;
	return ret; 
}

const char* extract_char(const char* string, size_t size) {
	char* final_str_f[(size_t)size];
	const char* final_str_l = (const char *)final_str_f;
	zero_string(final_str_l);
	char* final_str = (char *)final_str_l;
	for (size_t i = 0; i < size; i++) {
		final_str[i] = string[i];
	}
	return (const char*)final_str;
}

const char* extract_last_chars(const char* string, size_t size) {
	char* final_str_f[strlen(string)];
	const char* final_str_l = (const char *)final_str_f;
	zero_string(final_str_l);
	char* final_str = (char *)final_str_l;
	size_t len = strlen(string);
	final_str = (char *)&string[len - size];
	return (const char*)final_str;
}


const char* run(const char* com) {
	const char* echo_check_char = extract_char(com, 5);
	if (strcmp(com, "help") == 0) {
		writes("\nGeo OS v0.0.1\nMade by Nuno F.\n", 0, 15);
		com = zero_string(com);
		writes(">", 0, 15);
		return com;
	}
	if (strcmp(com, "clear") == 0) {
		terminal_cls();
		x = 0;
		y = 0;
		update_videoptr();
		com = zero_string(com);
		writes(">", 0, 15);
		return com;
	}
	if (strcmp(com, "command") == 0) {
		writes("\nWelcome to GEO OS 1.0. There are currently 3 commands:\n", 0, 15);
		writes("HELP: Shows version information about this OS.\n", 0, 15);
		writes("CLEAR: Clears the screen.\n", 0, 15);
		writes("COMMAND: The current command you are executing.\n", 0, 15);
		writes("--------------------\n", 0, 15);
		com = zero_string(com);
		writes(">", 0, 15);
		return com;
	}
	if (strcmp(echo_check_char, "echo ") == 0) {
		size_t size = strlen(com);
		for (size_t i = 0; i <= 5; i++) {
			size--; // Decrement size.
		}
		const char* value = extract_last_chars(com, size);
		writes(value, 0, 15);
		writes("\n", 0, 15);
		com = zero_string(com);
		writes(">", 0, 15);
		return com;
	}
	if (strcmp(com, "clear") != 0 && strcmp(com, "help") != 0 && strcmp(com, "command") != 0 && strcmp(echo_check_char, "echo ") != 0) {
		writes("\nUnknown command '", 0, 15);
		writes(command, 0, 15);
		writes("'", 0, 15);
		newline();
		com = zero_string(com);
		writes(">", 0, 15);
		return com;
	}
	return com;
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