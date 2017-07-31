/*
HEX/Base64 Functions

by. Cory Chiang
*/

#ifndef __HEX64_H_
#define __HEX64_H_

#define BASE64_CODE62	'+'
#define BASE64_CODE63	'/'

int HEX64_readHEX(unsigned char *buffer, char *str, int len);
int HEX64_readBase64(unsigned char *buffer, char *str, int len);

int HEX64_writeHEX(char *str, unsigned char *buffer, int len, unsigned char caps);
int HEX64_writeBase64(char *str, unsigned char *buffer, int len);

#endif