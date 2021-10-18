#pragma once

#include "../Private/Bridge.h"

#ifdef RTCL_ENABLED

#define RTCL_ADD_TYPE_SCOPE(...) RTCL::Bridge::AddScope({ ##__VA_ARGS__ });

#define RTCL_ADD_VAR_SCOPE(...) RTCL::Bridge::AddScope({ __VA_ARGS__ });

#define RTCL_ADD_VAR(...) RTCL::Bridge::AddVar(__VA_ARGS__);

#define RTCL_ADD_CALLBACK_BLOCK(functionBody) \
\
	functionBody \

#define RTCL_END_SCOPE()

#define RTCL_END_ALL_SCOPES()

#define RTCL_DESTRUCTOR(scope)

#else

#define RTCL_ADD_TYPE_SCOPE(...)

#define RTCL_ADD_VAR_SCOPE(...)

#define RTCL_ADD_VAR(...)

#define RTCL_ADD_CALLBACK_BLOCK(functionBody) 

#define RTCL_END_SCOPE()

#define RTCL_END_ALL_SCOPES()

#define RTCL_DESTRUCTOR(scope)

#endif // RTCL_ENABLED