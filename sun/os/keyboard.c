#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "keyboard.h"
#include "io.h"

char ScanCodeToASCII(uint8_t scan_code, bool shift) {
    switch (scan_code) {
        case 0x1E: return shift ? 'A' : 'a';
        case 0x30: return shift ? 'B' : 'b';
        case 0x2E: return shift ? 'C' : 'c';
        case 0x20: return shift ? 'D' : 'd';
        case 0x12: return shift ? 'E' : 'e';
        case 0x21: return shift ? 'F' : 'f';
        case 0x22: return shift ? 'G' : 'g';
        case 0x23: return shift ? 'H' : 'h';
        case 0x17: return shift ? 'I' : 'i';
        case 0x24: return shift ? 'J' : 'j';
        case 0x25: return shift ? 'K' : 'k';
        case 0x26: return shift ? 'L' : 'l';
        case 0x32: return shift ? 'M' : 'm';
        case 0x31: return shift ? 'N' : 'n';
        case 24: return shift ? 'O' : 'o';
        case 0x19: return shift ? 'P' : 'p';
        case 0x10: return shift ? 'Q' : 'q';
        case 0x13: return shift ? 'R' : 'r';
        case 31: return shift ? 'S' : 's';
        case 0x14: return shift ? 'T' : 't';
        case 0x15: return shift ? 'Y' : 'y';
        case 22: return shift ? 'U' : 'u';
        case 47: return shift ? 'V' : 'v';
        case 0x2D: return shift ? 'X' : 'x';
        case 17: return shift ? 'W' : 'w';
        case 0x28: return shift ? 'Y' : 'y';
        case 44: return shift ? 'Z' : 'z';
        
        // Numbers 0-9
        case 0xB: return shift ? '!' : '0';
        case 0x2: return shift ? '@' : '1';
        case 0x3: return shift ? '#' : '2';
        case 0x4: return shift ? '$' : '3';
        case 0x5: return shift ? '%' : '4';
        case 0x6: return shift ? '^' : '5';
        case 0x7: return shift ? '&' : '6';
        case 0x8: return shift ? '*' : '7';
        case 0x9: return shift ? '(' : '8';
        case 0xA: return shift ? ')' : '9';
        
        // Punctuation
        case 0x39: return ' '; // Space
        case 0x4A: return shift ? '_' : '-'; // Minus
        case 0x4C: return shift ? '+' : '='; // Equal
        case 0x35: return shift ? '~' : 0; // Grave
        case 0x33: return shift ? '{' : '['; // Left Bracket
        case 0x34: return shift ? '}' : ']'; // Right Bracket
        case 0x27: return shift ? ':' : ';'; // Semicolon
        case 0x37: return shift ? '"' : '\''; // Quote
        case 0x38: return shift ? '<' : ','; // Comma
        case 0x36: return shift ? '>' : '.'; // Period
        case 0x4E: return shift ? '?' : '/'; // Slash
        
        // Other
        case 0x1C: return '\n'; // Enter
        case 0x0E: return '\b'; // Backspace
        case 0x5D: return 0; // Right Control
        case 0x5B: return 0; // Left Control
        case 0x3A: return 0; // Caps Lock
        case 0xE0: return 0; // Special keys like Shift, Alt
        
        default: return 0; // unknown
    }
}

bool shift_pressed = false;

char sys_read()
{
    // wait for a key press
    while (!(inb(0x64) & 0x01)); // output buffer must be full! wait

    uint8_t scan_code = inb(0x60);
    
    if (scan_code == 0x2A || scan_code == 0x36) {  // Left Shift (0x2A)
        shift_pressed = true;  // Set shift pressed
        return 0; // return a reserved value; we're waiting for a key press
    } 
    if (scan_code == 0x36) {  // Right Shift (0x36)
        shift_pressed = true;  // Set shift pressed
        return 0; // return a reserved value; we're waiting for a key press
    } 
    else if (scan_code == 0xAA || scan_code == 0xB6) { // Left Shift Release (0xAA) or Right Shift Release (0xB6)
        shift_pressed = false;
        return 0; // return a reserved value; we're waiting for a key press
    }
    else {
        char c = ScanCodeToASCII(scan_code, shift_pressed); // can return characters like \n too
        return c;
    }    
}
