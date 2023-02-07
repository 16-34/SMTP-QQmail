#include "Head.h"

int main() {
	// 初始化并连接QQ邮箱smtp服务器
	InitTCP();
	ConnectSrver("120.241.186.196", 25);
	ShowRecv();

	SendMsg("HELO / EHLO"); 
	ShowRecv();

	// 登陆
	SendMsg("AUTH LOGIN");
	ShowRecv();
	
	// 填充信息
	const char* Username = "";				// QQ邮箱用户名
	const char* Password = "";				// QQ邮箱授权码

	const char* RecipientBox = "";			// 收件人邮箱
	const char* Sender = "";				// 发件人
	const char* Title = "";					// 标题
	const char* Content = "";				// 正文

	// 账号
	char msg[1024] = { 0 };
	InitBase64();

	base64_encode(msg, Username);
	SendMsg(msg);
	ShowRecv();

	// 授权码
	memset(msg, 0, 1024);
	base64_encode(msg, Password);
	SendMsg(msg);
	ShowRecv();
	
	// 发件人邮箱
	sprintf_s(msg, 1024, "MAIL FROM:<%s>", Username);
	SendMsg(msg);
	ShowRecv();

	// 收件人邮箱
	sprintf_s(msg, 1024, "RCPT TO:<%s>", RecipientBox);
	SendMsg(msg);
	ShowRecv();

	// 数据体
	SendMsg("DATA");
	ShowRecv();

	// 信息头
	sprintf_s(
		msg, 1024,
		"From:%s\r\nSubject:%s\r\n",
		Sender, Title
		);
	SendMsg(msg);

	// 正文
	sprintf_s(msg, 1024, "%s\r\n.", Content);
	SendMsg(msg);
	ShowRecv();

	// 退出
	SendMsg("QUIT");
	ShowRecv();
}

// 初始化并创建套接字
void InitTCP() {
	// 打开网络权限
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 创建IPv4 TCP socket 
	s = socket(AF_INET, SOCK_STREAM, 0);
}

// 连接服务器
void ConnectSrver(const char* addr, int port) {
	// 指定ip地址与端口
	struct sockaddr_in Server;
	Server.sin_family = AF_INET;
	Server.sin_addr.S_un.S_addr = inet_addr(addr);
	Server.sin_port = htons(port);
	connect(s, (struct sockaddr*)&Server, sizeof(struct sockaddr));
}

// 发送信息
void SendMsg(const char* msg) {
	printf("%s\n", msg);
	char buf[1024];
	// 添加后缀
	sprintf_s(buf, 1024, "%s\r\n", msg);
	send(s, buf, strlen(buf), 0);
}

// 接收信息并显示
void ShowRecv() {
	char buf[1024] = { 0 };
	recv(s, buf, 1024, 0);
	printf("%s\n", buf);
}