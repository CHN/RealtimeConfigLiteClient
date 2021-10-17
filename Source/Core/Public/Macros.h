#pragma once

#ifdef RTCL_ENABLED

#define RTCL_VARIABLE(...)

#define RTCL_UPDATE_BLOCK(functionBody) \
\
	functionBody \

#define RTCL_DESTRUCTOR()

#else

#define RTCL_VARIABLE(...)

#define RTCL_UPDATE_BLOCK(functionBody) functionBody

#define RTCL_DESTRUCTOR()

#endif // RTCL_ENABLED