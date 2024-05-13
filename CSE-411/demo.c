#include <stdio.h>

// Function to convert ASCII value to hexadecimal and store as char
char ascii_to_hex(char ch) {
    // Convert ASCII value to hexadecimal
    char hex = (ch >= '0' && ch <= '9') ? ch - '0' : (ch & 0x0F) + 9;
    hex &= 0x0F; // Make sure it's in the range 0-15
    return hex;
}

// Function to convert hexadecimal value stored as char back to ASCII
char hex_to_ascii(char hex) {
    // Convert hexadecimal to ASCII
    char ch = (hex <= 9) ? hex + '0' : (hex - 10) + 'A';
    return ch;
}

int main() {
    // Example ASCII character
    char ascii_char = 'A';
    
    // Convert ASCII to hexadecimal and store as char
    int hex_char = ascii_to_hex(ascii_char);
    
    printf("ASCII value of %c in hexadecimal: %d\n", ascii_char, hex_char);
    
    // Convert hexadecimal char back to ASCII
    char converted_ascii_char = hex_to_ascii(hex_char);
    
    printf("Hexadecimal value %d converted back to ASCII: %c\n", hex_char, converted_ascii_char);

    return 0;
}
