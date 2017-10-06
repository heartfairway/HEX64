# HEX64
## Overview
HEX64 is a set of functions for reading data encoded in HEX or Base64 to memory buffer, and encoding data into HEX or Base64 from memory buffer.
## Function List

** int HEX64_readHEX(unsigned char *buffer, char *str, int len) **
Reading HEX encoded data in to memory buffer,
unsigned char *buffer: destination buffer pointer,
char *str: source string pointer, 
int len: number of digits to read, 0 for un-limited, any non-HEX digit would treat as the end of HEX string,
return value: length data read into buffer, in bytes. 

** int HEX64_readBase64(unsigned char *buffer, char *str, int len) **
Reading Base64 encoded data in to memory buffer,
unsigned char *buffer: destination buffer pointer,
char *str: source string pointer, 
int len: number of characters to read, 0 for un-limited, any non-Base64 character would treat as the end of string,
return value: length data read into buffer, in bytes. 
