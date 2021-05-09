#ifndef __FONT_H_
#define __FONT_H_


#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
* 도꺠비 8x4x4 조합형 폰트
*/

/**

> 한글 구조
초성 글자 : ㄱ ㄴ ㄷ ㄹ ㅁ ㅂ ㅅ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ ㄲ ㄸ ㅃ ㅆ ㅉ (19개)
중성 글자 : ㅏ ㅑ ㅓ ㅕ ㅗ ㅛ ㅜ ㅠ ㅡ ㅣ ㅐ ㅒ ㅔ ㅖ ㅘ ㅙ ㅚ ㅝ ㅞ ㅟ ㅢ (21개)
받침 글자 : (없음) ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ (1 + 27개)

> 조합형 한글 폰트 (8x4x4) 구성
초성 : 총 8벌 (8줄)
    1벌 : 받침없는 [ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅣ] 와 결합
    2벌 : 받침없는 [ㅗ ㅛ ㅡ]
    3벌 : 받침없는 [ㅜ ㅠ]
    4벌 : 받침없는 [ㅘ ㅙ ㅚ ㅢ]
    5벌 : 받침없는 [ㅝ ㅞ ㅟ]
    6벌 : 받침 있는 [ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅣ] 와 결합
    7벌 : 받침있는 [ㅗ ㅛ ㅜ ㅠ ㅡ]
    8벌 : 받침있는 [ㅘ ㅙ ㅚ ㅢ ㅝ ㅞ ㅟ]
중성 : 총 4벌 (4줄)
    1벌 : 받침없는 [ㄱ ㅋ] 와 결합 (EX : 괴, 가, 큐, 캬)
    2벌 : 받침없는 [ㄱ ㅋ] 이외의 자음과 결합 (EX : 외, 나, 류, 먀)
    2벌 : 받침 있는 [ㄱ ㅋ] 와 결합 (EX : 광, 쾅, 굉, 괽)
    3벌 : 받침있는 [ㄱ ㅋ] 이외의 자음과 결합 (EX : 웅, 얅, 약, 약)
종성 : 총 4벌 (4줄)
    1벌 : 중성 [ㅏ ㅑ ㅘ] 와 결합
    2벌 : 중성 [ㅓ ㅕ ㅚ ㅝ ㅟ ㅢ ㅣ]
    3벌 : 중성 [ㅐ ㅒ ㅔ ㅖ ㅙ ㅞ]
    4벌 : 중성 [ㅗ ㅛ ㅜ ㅠ ㅡ]
*/

#define NTYPES1 8  /// 한글 초성 벌수
#define NTYPES2 4  /// 한글 중성 벌수
#define NTYPES3 4  /// 한글 종성 벌수

#define NHAN1 19  /// 한글 초성 문자수
#define NHAN2 21  /// 한글 중성 문자수
#define NHAN3 27  /// 한글 종성 문자수 (종성 없는 경우 제외)
#define NENG  95  /// 영어 문자수 ('!' 부터 '~' 까지)
#define NEXT  2   /// 특수문자 (빈 문자와 무효 문자)

/// <summary>
/// 8x4x4 한글 폰트 인덱스 테이블
/// </summary>

// 중성에 따른 초성 종류 / 받침 있음/없음
extern const char Type1ByType2andType3Table[2][NHAN2];

// 초성에 따른 중성 종류 / 받침 있음/없음
extern const char Type2ByType1andType3Table[2][NHAN1];

// 중성에 따른 종성 종류
extern const char Type3ByType2Table[NHAN2+1];

/// <summary>
/// 8x4x4 한글 폰트 (16x16)
/// </summary>

// 한글 초성 폰트
extern const unsigned short HanFont1[NTYPES1 * NHAN1][16];

// 한글 중성 폰트
extern const unsigned short HanFont2[NTYPES2 * NHAN2][16];

// 한글 종성 폰트
extern const unsigned short HanFont3[NTYPES3 * NHAN3][16];


/// <summary>
/// 영문 폰트 (8x16)
/// </summary>

// 영문 폰트 ('!' 부터 '~' 까지)
extern const unsigned char EngFont[NENG][16];

// 특수문자 (빈 문자와 무효 문자)
extern const unsigned char ExtFont[NEXT][16];


/// <summary>
/// 유니코드로 한글 코드로 폰트 이미지를 얻는다.
/// </summary>
/// <param name="c">유니코드 문자</param>
/// <param name="widthByte">수평 바이트 크기 포인터</param>
/// <param name="output">폰트 출력 버퍼. word aligned 되어 있어야 한다.</param>
/// <returns>16x16 비트맵 이미지 포인터</returns>
unsigned char* GetFontImage(unsigned short c, int* widthByte = NULL, unsigned char* output = NULL);


#if __cplusplus
}
#endif

#endif
