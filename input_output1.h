#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream> //파일입출력을 위한 헤더파일
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS;
//using namespace std;
struct gamers {
	char *name;
	int point;
};
void user_input_output(char name, int points,struct gamers **s, int top);
int ReadFile(struct gamers **s);
void intop(int top, struct gamers **s);
#endif