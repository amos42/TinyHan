#ifndef __UTF8_H_
#define __UTF8_h_

#ifdef __cplusplus
extern "C" {
#endif


/// <summary>
/// UTF8 문자열을 Unicode 문자열로 변환
/// </summary>
/// <param name="str">UTF8 입력 문자열</param>
/// <param name="output">Unicode 출력 문자열 버퍼</param>
/// <returns>결과 문자열 포인터</returns>
wchar_t* utf8_to_usc2(char* str, wchar_t *output);


#if __cplusplus
}
#endif

#endif