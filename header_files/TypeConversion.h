// TypeConversion.h
#pragma once

#include <string>

char* WCharToChar(const std::wstring& str);

LPCWSTR ConvertToLPCWSTR(const std::string& str);

std::wstring Utf8ToUtf16(const std::string& str);

LPCWSTR ConvertToLPCWSTR(const std::wstring& str);
