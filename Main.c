#include "Head.h"

int main() {
	// ��ʼ��������QQ����smtp������
	InitTCP();
	ConnectSrver("120.241.186.196", 25);
	ShowRecv();

	SendMsg("HELO / EHLO"); 
	ShowRecv();

	// ��½
	SendMsg("AUTH LOGIN");
	ShowRecv();
	
	// �����Ϣ
	const char* Username = "";				// QQ�����û���
	const char* Password = "";				// QQ������Ȩ��

	const char* RecipientBox = "";			// �ռ�������
	const char* Sender = "";				// ������
	const char* Title = "";					// ����
	const char* Content = "";				// ����

	// �˺�
	char msg[1024] = { 0 };
	InitBase64();

	base64_encode(msg, Username);
	SendMsg(msg);
	ShowRecv();

	// ��Ȩ��
	memset(msg, 0, 1024);
	base64_encode(msg, Password);
	SendMsg(msg);
	ShowRecv();
	
	// ����������
	sprintf_s(msg, 1024, "MAIL FROM:<%s>", Username);
	SendMsg(msg);
	ShowRecv();

	// �ռ�������
	sprintf_s(msg, 1024, "RCPT TO:<%s>", RecipientBox);
	SendMsg(msg);
	ShowRecv();

	// ������
	SendMsg("DATA");
	ShowRecv();

	// ��Ϣͷ
	sprintf_s(
		msg, 1024,
		"From:%s\r\nSubject:%s\r\n",
		Sender, Title
		);
	SendMsg(msg);

	// ����
	sprintf_s(msg, 1024, "%s\r\n.", Content);
	SendMsg(msg);
	ShowRecv();

	// �˳�
	SendMsg("QUIT");
	ShowRecv();
}

// ��ʼ���������׽���
void InitTCP() {
	// ������Ȩ��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ����IPv4 TCP socket 
	s = socket(AF_INET, SOCK_STREAM, 0);
}

// ���ӷ�����
void ConnectSrver(const char* addr, int port) {
	// ָ��ip��ַ��˿�
	struct sockaddr_in Server;
	Server.sin_family = AF_INET;
	Server.sin_addr.S_un.S_addr = inet_addr(addr);
	Server.sin_port = htons(port);
	connect(s, (struct sockaddr*)&Server, sizeof(struct sockaddr));
}

// ������Ϣ
void SendMsg(const char* msg) {
	printf("%s\n", msg);
	char buf[1024];
	// ��Ӻ�׺
	sprintf_s(buf, 1024, "%s\r\n", msg);
	send(s, buf, strlen(buf), 0);
}

// ������Ϣ����ʾ
void ShowRecv() {
	char buf[1024] = { 0 };
	recv(s, buf, 1024, 0);
	printf("%s\n", buf);
}