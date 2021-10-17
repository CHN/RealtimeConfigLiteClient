#include "Macros.h"
#include "ConfigClient.h"


#include <iostream>

// TESTING PURPOSES, ENTRY POINT SHOULD BE CALLED FROM TARGET APP

#include <windows.h>

int main()
{
	ConfigClient cc;
	cc.ConnectToServer("localhost", "5555");
	
	while (1)
	{
		static char x[2];
		x[0]++;
		cc.WriteBytes(x, 2);

		Sleep(200);
	}


	return 0;
}