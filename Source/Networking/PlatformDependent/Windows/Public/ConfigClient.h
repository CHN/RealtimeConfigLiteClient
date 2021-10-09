#pragma once

#include <winsock2.h>

class ConfigClient
{
public:
	bool ConnectToServer(const char* const ip, const char* const port);
	void CloseSocket();
	void WriteBytes(const char* const buffer, size_t bufferLength);

	~ConfigClient();

private:

	SOCKET ConnectSocket = INVALID_SOCKET;
};