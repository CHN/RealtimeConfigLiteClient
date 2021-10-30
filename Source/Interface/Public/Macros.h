#pragma once

#include "Bridge.h"

#ifdef RTCL_ENABLED

#define RTCL_ADD_TYPE_SCOPE(SCOPE) RTCL::Bridge::AddScope(##SCOPE);

#define RTCL_ADD_VAR_SCOPE(SCOPE) RTCL::Bridge::AddScope(SCOPE);

#define RTCL_ADD_VAR(...) RTCL::Bridge::AddVar(__VA_ARGS__);

#define RTCL_ADD_CALLBACK_BLOCK(functionBody) \
\
{ \
	functionBody \
	RTCL::Bridge::AddOnUpdateCallback(functionBody); \
}

#define RTCL_END_SCOPE() RTCL::Bridge::EndScope();

#define RTCL_END_ALL_SCOPES() RTCL::Bridge::EndAllScopes();

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