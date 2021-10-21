#pragma once

#include "DataCache.h"

#include <vector>
#include <string>

namespace RTCL
{
	class Bridge
	{
	public:
		
		static void AddScope(const std::string& scope);

		template<typename VariableType, typename ...VariableTypes>
		static void AddVar(VariableType variable, VariableTypes... variables)
		{
			AddVarInternal(variable);
			AddVar(variables...);
		}

		template<typename VariableType>
		static void AddVar(VariableType variable)
		{
			AddVarInternal(variable);
		}

		static void AddOnUpdateCallback(const std::function<DataCache::OnUpdateCallbackType>& callback);
		static void EndScope();
		static void EndAllScopes();

		static void PrintData();

	private:

		template<typename VariableType>
		static void AddVarInternal(VariableType variable)
		{
			dataCache.AddPointerToCurrentScope(variable, SerializedType::kInt);
		}

		static DataCache dataCache; // TODO: Consider rename this to data cache manager, if it suits
	};
}