// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "FONT.h"
#include "UTF8.h"


/// <summary>
/// 폰트 이미지를 클리핑하여 찍는다.
/// </summary>
/// <param name="freamBuffer">프레임 버퍼</param>
/// <param name="frameWidth">프레임 버퍼의 수평 크기</param>
/// <param name="frameHeight">프레임 버퍼의 수직 크기</param>
/// <param name="fontImage">폰트 이미지</param>
/// <param name="fontImageWidthByte">폰트 이미지의 수평 바이트 수</param>
/// <param name="fontImageHeight">폰트 이미지의 수직 크기</param>
/// <param name="offsetX">폰트 출력 수평 offset</param>
/// <param name="offsetY">폰트 출력 수직 offset</param>
/// <param name="colorIndex">출력 컬러 인덱스</param>
void PutImage(unsigned char* freamBuffer, int frameWidth, int frameHeight, unsigned char* fontImage, int fontImageWidthByte, int fontImageHeight, int offsetX, int offsetY, unsigned char colorIndex)
{
    // 화면우측이나 아래로 벗어나면 종료
    if (offsetY >= frameHeight || offsetX >= frameWidth) return;

    int imageWidth = fontImageWidthByte * 8;

    // 화면 좌측이나 위로 벗어나면 종료
    if (offsetY + fontImageHeight < 0 || offsetX + imageWidth < 0) return;

    unsigned char* sp = fontImage;

    // 윗쪽 클리핑
    if (offsetY < 0) {
        int th = -offsetY;
        offsetY = 0;
        sp += th * fontImageWidthByte;
        fontImageHeight -= th;
    }

    // 아랫쪽 클리핑
    if (offsetY + fontImageHeight > frameHeight) {
        fontImageHeight -= offsetY + fontImageHeight - frameHeight;
    }

    int firstSkip = 0;
    int lastSkip = 0;

    // 왼쪽 클리핑
    if (offsetX < 0) {
        int tw = -offsetX;
        offsetX = 0;
        firstSkip = tw % 8;

        sp += tw / 8;
        lastSkip += tw / 8;
        imageWidth -= tw;
    }

    // 오른쪽 클리핑
    if (offsetX + imageWidth > frameWidth) {
        imageWidth -= offsetX + imageWidth - frameWidth;
    }

    unsigned char* tp = freamBuffer + offsetY * frameWidth + offsetX;

    for (int i = 0; i < fontImageHeight; i++) {
        unsigned char v = *sp++;
        int k = firstSkip;
        v <<= firstSkip;

        for (int j = 0; j < imageWidth; j++) {
            if (v & 0x80) {
                *tp = colorIndex;
            }
            tp++;

            if (++k < 8) {
                v <<= 1;
            }
            else {
                if (j < imageWidth - 1) v = *sp++;
                k = 0;
            }
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
    const wchar_t* str = L"안녕Ab123 \x1\x1";
    //const wchar_t* str = L"안";
    const char* utfstr = "\x55\x54\x46\x2D\x38\x20\xEC\x9D\xB8\xEC\xBD\x94\xEB\x94\xA9";

    wchar_t* ptr = (wchar_t*)str;
    //wchar_t* ptr = utf8_to_usc2((char*)utfstr, (wchar_t*)output0);

    //int len = wcslen(ptr);
    int frameWidth = 80;
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
            PutImage(frameBuffer, frameWidth, 16, img, widthByte, frameHeight, x-3, -3, 0xff);
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
