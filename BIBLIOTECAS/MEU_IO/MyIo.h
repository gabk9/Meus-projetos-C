#ifndef MYIO_H
#define MYIO_H

#include <windows.h>

void readInt(int *out, int errorColor);
void readChar(char *out, int errorColor);
void readString(char *out, int maxLen, int errorColor);
void readFloat(float *out, int errorColor);
void cleanInput();

#endif
