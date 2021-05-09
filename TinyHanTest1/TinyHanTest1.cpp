// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "FONT.h"
#include "UTF8.h"


void PutImage(unsigned char* freamBuffer, int frameWidth, int frameHeight, unsigned char* imageBuffer, int imageWidthByte, int imageHeight, int startX, int startY, unsigned char color)
{
    // 화면우측이나 아래로 벗어나면 종료
    if (startY >= frameHeight || startX >= frameWidth) return;

    int imageWidth = imageWidthByte * 8;

    // 화면 좌측이나 위로 벗어나면 종료
    if (startY + imageHeight < 0 || startX + imageWidth < 0) return;

    unsigned char* sp = imageBuffer;

    // 윗쪽 클리핑
    if (startY < 0) {
        int th = -startY;
        startY = 0;
        sp += th * imageWidthByte;
    }

    // 아랫쪽 클리핑
    if (startY + imageHeight > frameHeight) {
        imageHeight -= startY + imageHeight - frameHeight;
    }

    int firstSkip = 0;
    int lastSkip = 0;

    // 왼쪽 클리핑
    if (startX < 0) {
        int tw = -startX;
        startX = 0;
        firstSkip = tw % 8;

        sp += tw / 8;
        lastSkip += tw / 8;
    }

    // 오른쪽 클리핑
    if (startX + imageWidth > frameWidth) {
        imageWidth -= startX + imageWidth - frameWidth;
    }

    unsigned char* tp = freamBuffer + startY * frameWidth + startX;

    for (int i = 0; i < imageHeight; i++) {
        unsigned char v = *sp++;
        int k = firstSkip;
        v <<= firstSkip;

        for (int j = 0; j < imageWidth; j++, k++) {
            if (v & 0x80) {
                *tp = color;
            }
            tp++;

            if (k >= 8) {
                if(j < imageWidth-1)
                    v = *sp++;
                k = 0;
                continue;
            }

            v <<= 1;
        }

        sp += lastSkip;
        tp += frameWidth - imageWidth;
    }

}


int main(int argc, char* argv[])
{
    unsigned char output0[16 * 2];
    unsigned char output[16 * 2];

    // 유니코드 문자열
    //const wchar_t* str = L"안녕Ab12345678910123";
    const wchar_t* str = L"안";
    const char* utfstr = "\x55\x54\x46\x2D\x38\x20\xEC\x9D\xB8\xEC\xBD\x94\xEB\x94\xA9";

    wchar_t* ptr = (wchar_t*)str;
    //wchar_t* ptr = utf8_to_usc2((char*)utfstr, (wchar_t*)output0);

    //int len = wcslen(ptr);
    int frameWidth = 120;
    int frameHeight = 16;

    unsigned char *frameBuffer = new unsigned char[frameWidth * frameHeight];
    memset(frameBuffer, 0, frameWidth * frameHeight);

    int x = 0;
    wchar_t ch;
    while ((ch = *ptr++) != L'\0')
    {
        int widthByte;
        unsigned char* img = GetFontImage(ch, &widthByte, output);

        if (img != NULL) 
        {
            PutImage(frameBuffer, frameWidth, 16, img, widthByte, frameHeight, x, 0, 0xff);
            x += widthByte * 8;
        }
        else {
            x += 8;
            // 빈 여백 찍기
        }

    }

    unsigned char* p = frameBuffer;
    for (int i = 0; i < frameHeight; i++) {
        for (int j = 0; j < frameWidth; j++) {
            unsigned char v = *p++;
            if (v != 0) {
                printf("*");
            }
            else 
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    delete[] frameBuffer;
}
