#ifndef __UTF8_H_
#define __UTF8_h_

#ifdef __cplusplus
extern "C" {
#endif

wchar_t* utf8_to_usc2(char* str, wchar_t *output);

#if __cplusplus
}
#endif

#endif