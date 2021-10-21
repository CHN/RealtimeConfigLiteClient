#include "DataCache.h"

#include <memory>
#include <iostream>

RTCL::DataCache::DataCache()
{
	dataCache.reserve(preAllocatedDataCacheSize);
}

void RTCL::DataCache::AddScope(const std::string& scope)
{
	auto* newScope = new DataScope();
	newScope->parent = currentScope;
	newScope->scope = scope;

	std::shared_ptr<DataScope> newScopeSharedPtr(newScope);

	if (currentScope.expired())
	{
		dataCache.emplace_back(newScopeSharedPtr);
	}
	else
	{
		currentScope.lock()->children.emplace_back(newScopeSharedPtr);
	}

	currentScope = newScopeSharedPtr;

	currentScopeHierarchy.push_back(scope);
}

void RTCL::DataCache::AddOnUpdateCallbackToCurrentScope(const std::function<OnUpdateCallbackType>& callback)
{
	currentScope.lock()->onUpdateCallbacks.push_back(callback);
}

void RTCL::DataCache::AddPointerToCurrentScope(void* pointer, SerializedType type)
{
	currentScope.lock()->pointerVectorMap[type].push_back(pointer);
}

void RTCL::DataCache::AddPointerListToCurrentScope(const std::vector<void*>& pointers, SerializedType type)
{
	auto& pointerVector = currentScope.lock()->pointerVectorMap[type];
	pointerVector.insert(pointerVector.end(), pointers.begin(), pointers.end());
}

void RTCL::DataCache::EndScope()
{
	// add asserts

	currentScopeHierarchy.pop_back();

	if (currentScopeHierarchy.empty())
	{
		currentScope.reset();
	}
	else
	{
		currentScope = currentScope.lock()->parent;
	}
}

void RTCL::DataCache::EndAllScopes()
{
	// add asserts

	currentScopeHierarchy.clear();
	currentScope.reset();
}

// TEST: Only for testing purposes, so not optimized and cleaned
void RTCL::DataCache::PrintData()
{
	for (auto& parent : dataCache)
	{
		PrintDataInternal(parent.get(), 0);
	}
}

// TEST: Only for testing purposes, so not optimized and cleaned
void RTCL::DataCache::PrintDataInternal(DataScope* scope, int indent)
{
	PrintIndent(indent);
	std::cout << "Scope: " << scope->scope << std::endl;

	for (const auto& ptrPair : scope->pointerVectorMap)
	{
		PrintIndent(indent + 1);
		std::cout << "Type: " << static_cast<int>(ptrPair.first) << std::endl;

		for (const auto* ptr : ptrPair.second)
		{
			PrintIndent(indent + 2);
			std::cout << "Pointer: " << (unsigned long long)ptr << std::endl;
		}
	}

	std::cout << std::endl;

	for (auto& child : scope->children)
	{
		PrintDataInternal(child.get(), indent + 3);
	}
}

// TEST: Only for testing purposes, so not optimized and cleaned
void RTCL::DataCache::PrintIndent(int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		std::cout << "\t";
	}
}
