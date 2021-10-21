#include "Macros.h"
#include "ConfigClient.h"


#include <iostream>

// TESTING PURPOSES, ENTRY POINT SHOULD BE CALLED FROM TARGET APP

#include <windows.h>

int main()
{
	RTCL_ADD_TYPE_SCOPE("inner1");
	int x = 42; const char* y = "test";
	RTCL_ADD_VAR(&x, &y);

		RTCL_ADD_TYPE_SCOPE("inner11");
		RTCL_ADD_VAR(&x, &y);

			RTCL_ADD_TYPE_SCOPE("inner111");
			RTCL_ADD_VAR(&x, &y);
			RTCL_END_SCOPE();

			RTCL_ADD_TYPE_SCOPE("inner112");
			RTCL_ADD_VAR(&x, &y);
			RTCL_END_ALL_SCOPES();

		

		RTCL_ADD_TYPE_SCOPE("inner12");
		RTCL_ADD_VAR(&x, &y);

			RTCL_ADD_TYPE_SCOPE("inner121");
			RTCL_ADD_VAR(&x, &y);

				RTCL_ADD_TYPE_SCOPE("inner1211");
				RTCL_ADD_VAR(&x, &y);
				RTCL_END_SCOPE();

				RTCL_ADD_TYPE_SCOPE("inner1212");
				RTCL_ADD_VAR(&x, &y);
				RTCL_END_SCOPE();

			RTCL_END_SCOPE();

		RTCL_END_SCOPE();


	RTCL::Bridge::PrintData();

	return 0;

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