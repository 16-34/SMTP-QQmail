#include "Base64.h"

char code[64];

// 获取字符串长度(包括'\0')
unsigned length(const char* str) {
	unsigned len = 1;
	while (str[len])
		len++;

	return len;
}

// 24位映射
void atob(char* buf, const char* src) {
	int temp, flag = 4;
	// 处理结尾
	if (src[0] == '\0') {
		buf[0] = '\0';
		return;
	}

	if (src[1] == '\0') {
		temp = (src[0] << 16);
		flag = 2;
	}
	else if (src[2] == '\0') {
		temp = (src[0] << 16) + (src[1] << 8);
		flag = 3;
	}
	else
		temp = (src[0] << 16) + (src[1] << 8) + src[2];

	// 映射
	int index = temp % 64;
	for (int i = 3; i > -1; i--) {
		buf[i] = code[index];
		temp >>= 6;
		index = temp % 64;
	}

	for (int i = flag; i < 4; i++)
		buf[i] = '=';
}

void InitBase64() {
	// 将base64码表填入code中
	int i = 0;
	for (; i < 26; i++)
		code[i] = i + 'A';

	for (; i < 52; i++)
		code[i] = i + 'a' - 26;

	for (; i < 62; i++)
		code[i] = i + '0' - 52;

	code[62] = '+';
	code[63] = '/';
}

void base64_encode(char* buf, const char* src) {
	unsigned len = length(src);
	unsigned i = 0, j = 0;
	// 拆分并编码
	for (; i < len; i += 3, j += 4)
		atob(buf + j, src + i);
}
