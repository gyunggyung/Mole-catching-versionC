#pragma warning(disable: 4996)
#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define _DO_NOT_DECLARE_INTERLOCKED_INTRINSICS_IN_MEMORY
struct gamers {
	char *name;
	int point;
};
void user_input_output(char name, int points,struct gamers **s, int top);
int ReadFile(struct gamers **s, char fn[30]);
void toprank(int k, struct gamers **s);
void intop(int k, struct gamers **s);
#endif