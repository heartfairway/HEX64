/*
 HEX/Base64 Functions
 
   by. Cory Chiang

   
BSD 3-Clause License

Copyright (c) 2017, Cory Chiang
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "hex64.h"

// declaration of inline functions, ref. C99 sec. 6.7.4
int _is_hex_digit(char s);
unsigned char _get_hex_value(char s);
int _is_base64_digit(char s);
unsigned char _get_base64_value(char s);
char _get_hex_char(unsigned char v, unsigned char caps);
char _get_base64_char(unsigned char v);
void _write_base64_unit(char *str, unsigned char *buffer);

inline int _is_hex_digit(char s)
{
	if( (s>=48 && s<=57) || (s>=65 && s<=70) || (s>=97 && s<=102) ) return 1;
	else return 0;
}

inline unsigned char _get_hex_value(char s)
{
	switch(s) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': case 'a': return 10;
		case 'B': case 'b': return 11;
		case 'C': case 'c': return 12;
		case 'D': case 'd': return 13;
		case 'E': case 'e': return 14;
		case 'F': case 'f': return 15;
	}
}

inline int _is_base64_digit(char s)
{
	if( (s>=48 && s<=57) || (s>=65 && s<=90) || (s>=97 && s<=122) || s==BASE64_CODE62 || s==BASE64_CODE63 ) return 1; // || s==61 // '=' can just ignored
	else return 0;
}

inline unsigned char _get_base64_value(char s)
{
	if(s>=65 && s<=90) return (s-65);		// A...Z  0...25
	if(s>=97 && s<=122) return (s-71);		// a...z  26...51
	if(s>=48 && s<=57) return (s+4);		// 0...9  52...61
	if(s==BASE64_CODE62) return 62;
	if(s==BASE64_CODE63) return 63;
	if(s==61) return 0;
}

inline char _get_hex_char(unsigned char v, unsigned char caps)
{
	if(v<10) return (char)(v+48);
	else {
		if(caps) return (char)(v+55); 	// 10...  A...
		else return (char)(v+87); 		// 10...  a...
	}
}

inline char _get_base64_char(unsigned char v)
{
	if(v<26) return (char)(v+65);		// 0...25  A...Z
	else if(v<52) return (char)(v+71);	// 26...51  a...z
	else if(v<62) return (char)(v-4);	// 52...61  0...90
	else if(v==62) return BASE64_CODE62;
	else if(v==63) return BASE64_CODE63;
}

inline void _write_base64_unit(char *str, unsigned char *buffer)
{
	str[0]=_get_base64_char(buffer[0]>>2);
	str[1]=_get_base64_char( ((buffer[0]<<4) | (buffer[1]>>4)) & 0x3f );
	str[2]=_get_base64_char( ((buffer[1]<<2) | (buffer[2]>>6)) & 0x3f );
	str[3]=_get_base64_char( buffer[2] & 0x3f );
}

int HEX64_readHEX(unsigned char *buffer, char *str, int len)
{
	int i=0;
	
	while(_is_hex_digit(str[i])) {
		if(i%2)	buffer[i/2]+=_get_hex_value(str[i]);	// 4 lower bits
		else buffer[i/2]=_get_hex_value(str[i])<<4;		// 4 higher bits
		
		if(++i==len) break; // makes len=0 denoting un-limited length
	}
	
	return (i+1)/2;
}

int HEX64_readBase64(unsigned char *buffer, char *str, int len)
{
	int i=0, k=0;
	
	while(_is_base64_digit(str[i])) {
		switch(i%4) {
			case 0:
				buffer[k]=_get_base64_value(str[i])<<2;
				break;
			case 1:
				buffer[k++]|=_get_base64_value(str[i])>>4;
				buffer[k]=_get_base64_value(str[i])<<4;
				break;
			case 2:
				buffer[k++]|=_get_base64_value(str[i])>>2;
				buffer[k]=_get_base64_value(str[i])<<6;
				break;
			case 3:
				buffer[k++]|=_get_base64_value(str[i]);
				break;
		} 
		
		if(++i==len) break; // makes len=0 denoting un-limited length
	}
	
	return k;
}

int HEX64_writeHEX(char *str, unsigned char *buffer, int len, unsigned char caps)
{
	int k;
	
	for(k=0; k<len; k++) {
		// higher bits
		*str=_get_hex_char(buffer[k]>>4, caps);
		str++;
		
		// lower bits
		*str=_get_hex_char(buffer[k]&0x0f, caps);
		str++;
	}
	*str='\0';
	
	return k*2;
}

int HEX64_writeBase64(char *str, unsigned char *buffer, int len)
{
	int sp, scnt, srmd;
	unsigned char temp[3];
	
	scnt=len/3;
	srmd=len%3;
	
	for(sp=0; sp<scnt; sp++) {
		_write_base64_unit(str, &buffer[sp*3]);
		str+=4;
	}

	
	if(srmd) {
		temp[0]=buffer[(sp*3)];
		
		if(srmd>1) temp[1]=buffer[(sp*3)+1];
		else temp[1]=0;
		
		temp[2]=0;
		
		_write_base64_unit(str, temp);
		str+=4;
		
		*(str-1)='=';
		if(srmd==1) *(str-2)='=';
		//sp++;
	}
	
	*str='\0';
	
	return sp*4;
}
