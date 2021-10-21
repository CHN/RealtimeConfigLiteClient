#include "DataCache.h"

#include <memory>
#include <iostream>

RTCL::DataCache::DataCache()
{
	dataCache.reserve(preAllocatedDataCacheSize);
}

void RTCL::DataCache::AddScope(const std::string& scope)
{
	if (currentScopeHierarchy.empty())
	{
		dataCache.emplace_back();

		++parentScopeCount;
	}

	auto& currentScopeVector = dataCache[parentScopeCount - 1];

	++currentActiveScopeCount;

	DataScope newScope;
	newScope.scope = scope;
	newScope.depth = currentActiveScopeCount - 1;
	currentScopeVector.emplace(currentScopeVector.begin() + (currentActiveScopeCount - 1), std::move(newScope));

	currentScope = &currentScopeVector[currentActiveScopeCount - 1]; // TODO: CHECK: It can be a bad idea to cache address of a vector element.

	currentScopeHierarchy.push_back(scope);
}

void RTCL::DataCache::AddOnUpdateCallbackToCurrentScope(const std::function<OnUpdateCallbackType>& callback)
{
	currentScope->onUpdateCallbacks.push_back(callback);
}

void RTCL::DataCache::AddPointerToCurrentScope(void* pointer, SerializedType type)
{
	currentScope->pointerVectorMap[type].push_back(pointer);
}

void RTCL::DataCache::AddPointerListToCurrentScope(const std::vector<void*>& pointers, SerializedType type)
{
	auto& pointerVector = currentScope->pointerVectorMap[type];
	pointerVector.insert(pointerVector.end(), pointers.begin(), pointers.end());
}

void RTCL::DataCache::EndScope()
{
	// add asserts

	--currentActiveScopeCount;

	currentScopeHierarchy.pop_back();

	if (currentScopeHierarchy.empty())
	{
		currentScope = nullptr;
	}
	else
	{
		currentScope = &dataCache[parentScopeCount - 1][currentActiveScopeCount - 1];
	}
}

void RTCL::DataCache::EndAllScopes()
{
	// add asserts

	currentActiveScopeCount = 0;
	currentScopeHierarchy.clear();

	currentScope = nullptr;
}

void RTCL::DataCache::PrintData()
{
	for (int pI = 0; pI < dataCache.size(); ++pI)
	{
		std::cout << "Parent Scope: " << pI << std::endl;

		int indent = 1;

		for (const auto& scope : dataCache[pI])
		{
			std::cout << std::endl;

			int indent2 = indent + scope.depth;

			for (int i = 0; i < indent2; ++i)
			{
				std::cout << "\t";
			}

			std::cout << "Scope: " << scope.scope << std::endl;

			++indent2;

			for (const auto& ptrPair : scope.pointerVectorMap)
			{
				for (int i = 0; i < indent2; ++i)
				{
					std::cout << "\t";
				}

				std::cout << "Type: " << static_cast<int>(ptrPair.first) << std::endl;

				for (void* ptr : ptrPair.second)
				{
					for (int i = 0; i < indent2 + 1; ++i)
					{
						std::cout << "\t";
					}

					std::cout << "Pointer: " << (unsigned long long)ptr << std::endl;
				}
			}
		}

		std::cout << std::endl;
	}
}
