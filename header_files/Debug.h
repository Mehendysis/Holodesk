//Debug.h
#pragma once
#include <iostream>
using namespace std;

#ifndef _DEBUG
#define DEBUG_MSG(x) 
#else
#define DEBUG_MSG(x) do { cerr << x << endl; } while (0)
#endif