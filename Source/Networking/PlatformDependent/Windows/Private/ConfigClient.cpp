#include "ConfigClient.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <cassert>

namespace
{
	constexpr int DEFAULT_BUFFER_LENGTH = 512;
}

bool ConfigClient::ConnectToServer(const char* const ip, const char* const port)
{
	assert(ConnectSocket == INVALID_SOCKET && "Already connected");

	WSADATA wsaData;
	
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	const char* sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFFER_LENGTH];
	int iResult;
	int recvbuflen = DEFAULT_BUFFER_LENGTH;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(ip, port, &hints, &result);
	if (iResult != 0) {
		WSACleanup();
		return false;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			WSACleanup();
			return false;
		}

		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
}

void ConfigClient::CloseSocket()
{
	assert(ConnectSocket != INVALID_SOCKET && "Client not connected to server");

	closesocket(ConnectSocket);
	WSACleanup();

	ConnectSocket = INVALID_SOCKET;
}

void ConfigClient::WriteBytes(const char* const buffer, size_t bufferLength)
{
	int result = send(ConnectSocket, buffer, bufferLength, 0);
	if (result == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		WSACleanup();
		
		//assert(false && "Buffer could not be sent. May be server is closed, this case must be handled");
	}
}

ConfigClient::~ConfigClient()
{
	if (ConnectSocket != INVALID_SOCKET)
	{
		CloseSocket();
	}
}
