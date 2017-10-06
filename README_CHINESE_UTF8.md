# HEX64
## 概觀
HEX64是一系列的涵式，可用來將經過HEX(16進位)或是Base64編碼的資料讀至位元組陣列，或是將位元組陣列輸出為HEX或Base64編碼字串。
## 涵式列表

int HEX64_readHEX(unsigned char *buffer, char *str, int len)
* 將HEX編碼之資料讀入位元陣列,
* unsigned char *buffer: 目標位元組陣列指標,
* char *str: 來源字串指標, 
* int len: 讀取的字數, 0表示無限制, 任何非HEX之字元將會視為來源字串的結尾,
* 回傳值: 讀取的位元組數目. 

int HEX64_readBase64(unsigned char *buffer, char *str, int len)
* 將Base64編碼之資料讀入位元陣列,
* unsigned char *buffer: 目標位元組陣列指標,
* char *str: 來源字串指標, 
* int len: 讀取的字數, 0表示無限制, 任何非Base64之字元將會視為來源字串的結尾,
* 回傳值: 讀取的位元組數目. 

int HEX64_writeHEX(char *str, unsigned char *buffer, int len, unsigned char caps)
* 將位元組陣列輸出成HEX編碼字串,
* char *str: 目標字串指標, 
* unsigned char *buffer: 來源位元組陣列指標,
* int len: 需要編碼的位元組數量,
* unsigned char caps: 是否於輸出字串中使用大寫字母，視為布林值,
* return value: 輸出字串的長度.

int HEX64_writeBase64(char *str, unsigned char *buffer, int len)
* 將位元組陣列輸出成Base64編碼字串,
* char *str: 目標字串指標, 
* unsigned char *buffer: 來源位元組陣列指標,
* int len: 需要編碼的位元組數量,
* return value: 輸出字串的長度.
