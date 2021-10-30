#pragma once

#include "SerializedTypeSelector.h"

#include <vector>
#include <string>
#include <functional>

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

		static void AddOnUpdateCallback(const std::function<void()>& callback);
		static void EndScope();
		static void EndAllScopes();

	private:

		template<typename VariableType>
		static void AddVarInternal(VariableType variable)
		{
			
		}
	};
}