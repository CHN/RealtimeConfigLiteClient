#pragma once

#include <vector>
#include <string>

namespace RTCL
{
	class Bridge
	{
	public:

		static void AddScope(std::vector<std::string> scopes);

		template<typename VariableType, typename ...VariableTypes>
		static void AddVar(VariableType variable, VariableTypes... variables)
		{
			
			AddVar(variables...);
		}

		template<typename VariableType>
		static void AddVar(VariableType variable)
		{
			
		}

	private:
	};
}