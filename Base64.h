#pragma once

// 初始化编码表
// (比较懒，没有一个一个输进数组)
void InitBase64();

// 编码字符串
// (因为临时写的，懒得处理安全性了，调用的时候buf的大小大于src的4/3就行)
void base64_encode(char* buf, const char* src);