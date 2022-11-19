#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <map>

class Wrapper
{
public:
	template <typename Obj, typename... Args>
	Wrapper(Obj* obj, int (Obj::*func)(Args...), std::vector<std::pair<std::string, int>> const& params)
	{
		for (auto& param : params)
		{
			_params.insert(param);
		}

		if (params.size() != _params.size())
		{
			throw std::exception("Params name should be unique");
		}
		
		_func = [obj, func](std::vector<int>& params)
		{
			return execFunc(obj, func, params, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	Wrapper(Wrapper const&) = delete;
	Wrapper& operator=(Wrapper const&) = delete;
	Wrapper(Wrapper&&) = default;
	Wrapper& operator=(Wrapper&&) = default;
	~Wrapper() = default;

	template <typename Obj, typename... Args, size_t... I>
	static int execFunc(Obj* obj, int (Obj::* func)(Args...), std::vector<int> const& params, std::index_sequence<I...>)
	{
		return (obj->*func)(params[I]...);
	}


	int execute(std::vector<std::pair<std::string, int>> const& params)
	{
		std::map<std::string, int> sortedParams;
		for (auto& param : params)
		{
			sortedParams.insert(param);
		}

		if (sortedParams.size() != _params.size())
		{
			throw std::exception("Params name should be unqiue");
		}
		
		std::vector<int> checkedParams;
		for (auto gettedParamIt = sortedParams.begin(), defaultParamIt = _params.begin(); gettedParamIt != sortedParams.end(); ++gettedParamIt, ++defaultParamIt)
		{
			if (gettedParamIt->first != defaultParamIt->first)
			{
				throw std::exception("Wrong args name");
			}

			checkedParams.push_back(gettedParamIt->second);
		}

		return _func(checkedParams);
	}
private:
	std::function<int(std::vector<int>&)> _func;
	std::map<std::string, int> _params;
};
