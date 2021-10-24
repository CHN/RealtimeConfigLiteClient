#include "DataCache.h"

#include "Serializer.h"

#include <memory>
#include <iostream>
#include <algorithm>

RTCL::DataCache::DataCache()
{
	dataCache.reserve(preAllocatedDataCacheSize);
}

void RTCL::DataCache::AddScope(const std::string& scopeName)
{
	std::shared_ptr<DataScope> newScope = std::make_shared<DataScope>();
	newScope->parent = currentScope;
	newScope->name = scopeName;

	if (currentScope.expired())
	{
		dataCache.emplace_back(newScope);
	}
	else
	{
		currentScope.lock()->children.emplace_back(newScope);
	}

	currentScope = newScope;
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

	currentScope = currentScope.lock()->parent;
}

void RTCL::DataCache::EndAllScopes()
{
	// add asserts

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
	std::cout << "Scope: " << scope->name << std::endl;

	for (const auto& ptrPair : scope->pointerVectorMap)
	{
		PrintIndent(indent + 1);
		std::cout << "Type: " << static_cast<int>(ptrPair.first) << std::endl;

		for (auto* ptr : ptrPair.second)
		{
			PrintIndent(indent + 2);
			std::cout << "Pointer: " << (unsigned long long)ptr << std::endl;

			PrintIndent(indent + 2);
			std::cout << "Serialized Value: ";

			auto serializedValue = Serializer::SerializeByEnumType(ptrPair.first, ptr);

			std::for_each(serializedValue.begin(), serializedValue.end(), [](char value)
				{
					std::cout << (int)value << "/";
				});

			std::cout << std::endl;
		}
	}

	std::cout << std::endl;

	for (const auto& child : scope->children)
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
