#pragma once

#include "Serializer.h"

#include <vector>
#include <string>
#include <map>
#include <functional>
#include <cstdint>

namespace RTCL
{
	class DataCache
	{
	public:

		using OnUpdateCallbackType = void();

		DataCache();

		void AddScope(const std::string& scope);
		void AddOnUpdateCallbackToCurrentScope(const std::function<OnUpdateCallbackType>& callback);
		void AddPointerToCurrentScope(void* pointer, RTCL::SerializedType type);
		void AddPointerListToCurrentScope(const std::vector<void*>& pointers, SerializedType type);
		void EndScope();
		void EndAllScopes();

		void PrintData();
	private:
		
		static constexpr size_t preAllocatedDataCacheSize = 100;
		static constexpr size_t nestedScopeMaxCount = 1000; // TODO: Not considered up to now

		using PointerListMapType = std::map<SerializedType, std::vector<void*>>;

		struct DataScope
		{
			int depth = 0; // TODO: Should be replaced with nested vectors for nested scopes
			std::string scope;
			std::vector<std::function<OnUpdateCallbackType>> onUpdateCallbacks;
			PointerListMapType pointerVectorMap;
		};

		using DataScopeVectorType = std::vector<DataScope>;

		size_t parentScopeCount = 0;
		size_t currentActiveScopeCount = 0;

		std::vector<DataScopeVectorType> dataCache;
		std::vector<std::string> currentScopeHierarchy;

		DataScope* currentScope = nullptr;
	};
}