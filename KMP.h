#pragma once
#include <iostream>
#include <cstring>
//return a index, -1 if not found
int KMP(char* superString, char* pattern, int start = 0);