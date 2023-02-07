#pragma once

#include <WinSock2.h>
#include <stdio.h>
#include "Base64.h"

#pragma comment(lib,"ws2_32.lib")

SOCKET s;

void InitTCP();

void ConnectSrver(const char* addr, int port);

void SendMsg(const char* msg);

void ShowRecv();