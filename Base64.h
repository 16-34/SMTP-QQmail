#pragma once

// ��ʼ�������
// (�Ƚ�����û��һ��һ���������)
void InitBase64();

// �����ַ���
// (��Ϊ��ʱд�ģ����ô���ȫ���ˣ����õ�ʱ��buf�Ĵ�С����src��4/3����)
void base64_encode(char* buf, const char* src);