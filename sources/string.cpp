#include <string.hpp>
#include <cstring>


char* CopyString(const char* str)
{
    unsigned i;
    for (i = 0; str[i] != '\0'; i++);
    char* result = new char[i + 1];
    std::memcpy(result, str, i + 1);
    return result;
}

char* ConcatenateStrings(const char* a, const char* b)
{
    unsigned len1, len2;
    for (len1 = 0; a[len1] != '\0'; len1++);
    for (len2 = 0; b[len2] != '\0'; len2++);
    char* result = new char[len1 + len2 + 1];
    std::memcpy(result, a, len1);
    std::memcpy(result + len1, b, len2 + 1);
    return result;
}