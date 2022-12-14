#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <vector>

class Wrapper
{
public:
	template <typename Subj, typename... Args>
	Wrapper(Subj* subj, int (Subj::*func)(Args...), std::vector<std::pair<std::string, int>> const& params)
	{
		for (auto& param : params)
		{
			_params.insert(param);
		}

		if (params.size() != _params.size())
		{
			throw std::exception("Duplicate parameter names");
		}
		
		_func = [subj, func](std::vector<int>& params)
		{
			return execCommand(subj, func, params, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	~Wrapper() = default;
	Wrapper(Wrapper const&) = delete;
	Wrapper& operator=(Wrapper const&) = delete;
	Wrapper(Wrapper&&) = default;
	Wrapper& operator=(Wrapper&&) = default;
	

	template <typename Subj, typename... Args, size_t... I>
	static int execCommand(Subj* obj, int (Subj::* func)(Args...), std::vector<int> const& params, std::index_sequence<I...>)
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
			throw std::exception("Duplicate parameter names");
		}
		
		std::vector<int> verifiedParams;
		for (auto receivedParam = sortedParams.begin(), initialParam = _params.begin(); receivedParam != sortedParams.end(); ++receivedParam, ++initialParam)
		{
			if (receivedParam->first != initialParam->first)
			{
				throw std::exception("Wrong arguments name");
			}

			verifiedParams.push_back(receivedParam->second);
		}

		return _func(verifiedParams);
	}
private:
	std::function<int(std::vector<int>&)> _func;
	std::map<std::string, int> _params;
};
