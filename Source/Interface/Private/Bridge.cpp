#include "Bridge.h"

RTCL::DataCache RTCL::Bridge::dataCache;

void RTCL::Bridge::AddScope(const std::string& scope)
{
	dataCache.AddScope(scope);
}

void RTCL::Bridge::AddOnUpdateCallback(const std::function<DataCache::OnUpdateCallbackType>& callback)
{
	dataCache.AddOnUpdateCallbackToCurrentScope(callback);
}

void RTCL::Bridge::EndScope()
{
	dataCache.EndScope();
}

void RTCL::Bridge::EndAllScopes()
{
	dataCache.EndAllScopes();
}

void RTCL::Bridge::PrintData()
{
	dataCache.PrintData();
}
