// Debug.h
#pragma once
#include <iostream>
//using namespace std;

#ifndef _DEBUG
#define DEBUG_MSG(x)
#else
void DEBUG_MSG(const char* message);
#endif