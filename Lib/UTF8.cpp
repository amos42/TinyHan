#include <stdio.h>
#include "UTF8.h"

/// <summary>
/// UTF8 문자열을 Unicode 문자열로 변환
/// </summary>
/// <param name="str">UTF8 입력 문자열</param>
/// <param name="output">Unicode 출력 문자열 버퍼</param>
/// <returns>결과 문자열 포인터</returns>
wchar_t* utf8_to_usc2(char* str, wchar_t *output) 
{
    unsigned char ch;
    wchar_t* p = output;
    while ((ch = *str++) != '\0') 
    {
        if (!(ch & 0x80)) {
            *p++ = (wchar_t)ch;
        }
        else if ((ch >> 5) == 0x6) {
            unsigned char ch2 = *str++;
            if ((ch2 >> 6) == 2) {
                *p++ = (((unsigned short)ch & 0x1F) << 6) | ((unsigned short)ch2 & 0x3F);
            }
        }
        else if ((ch >> 4) == 0xE) {
            unsigned char ch2 = *str++;
            if ((ch2 >> 6) == 2) {
                unsigned char ch3 = *str++;
                if ((ch3 >> 6) == 2) {
                    *p++ = (((unsigned short)ch & 0x0F) << 12) | (((unsigned short)ch2 & 0x3F) << 6) | ((unsigned short)ch3 & 0x3F);
                }
            }
        }
    }
    *p = L'\0';

    return output;
}
