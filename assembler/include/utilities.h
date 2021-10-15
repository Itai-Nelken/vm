#ifndef UTILITIES_H
#define UTILITIES_H
#include <string.h>

/******
 * Fill a string with 0's
 * 
 * @param s A string.
 ******/
void strzero(char *s);

/******
 * Shift the characters in a string one character left. "abcd" -> "bcd"
 * 
 * @param s A pointer to the string.
 ******/
void leftShift(char *s);

/******
 * Check if the string s contains one of the characters in c.
 * 
 * @param s The string.
 * @param c the characters.
 * 
 * @return 0 if 's' contains one of the characters, or 1 if it doesn't.
 ******/
int strcontains(char *s, const char *c);

/******
 * Convert a string containing digits to a int ("123" -> 123).
 * 
 * @param s The string.
 * 
 * @return The converted int.
 ******/
int str2int(char *s);

#endif // UTILITIES_H
