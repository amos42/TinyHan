// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include "FONT.h"


int main(int argc, char *argv[])
{
    unsigned char output[16 * 2];

    // 유니코드 문자열
    const wchar_t *str = L"안녕하세요Abc123";

    wchar_t* ptr = (wchar_t *)str;

    wchar_t ch;
    while((ch = *ptr++) != L'\0')
    {
        int widthByte;
        unsigned char* img = GetFontImage(ch, &widthByte, output);

        if(img != null) {
            unsigned char* p = img;
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < widthByte; j++) {
                    unsigned char v = *p++;
                    for (int k = 0; k < 8; k++) {
                        if (v & 0x80) {
                            printf("*");
                        }
                        else {
                            printf(" ");
                        }
                        v <<= 1;
                    }
                }
                printf("\n");
            }
        } else {
            // 빈 여백 찍기
        }
    }
}
