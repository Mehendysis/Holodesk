// TypeConversion.cpp

#include <Windows.h>
#include <string>
#include "TypeConversion.h"

// Convert a std::wstring to a char*
char* WCharToChar(const std::wstring& str)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char* buffer = new char[size];
    WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, buffer, size, nullptr, nullptr);
    return buffer;
}

LPCWSTR ConvertToLPCWSTR(const std::string& str)
{
    // Get the required buffer size
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

    // Allocate the buffer and convert the string
    wchar_t* buffer = new wchar_t[bufferSize];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, bufferSize);

    // Return the converted string as LPCWSTR
    return buffer;
}

// Convert a UTF-8 string to a UTF-16 string
std::wstring Utf8ToUtf16(const std::string& str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring result(size - 1, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);
    return result;
}

// Convert a UTF-16 string to a LPCWSTR
LPCWSTR ConvertToLPCWSTR(const std::wstring& str)
{
    return str.c_str();
}