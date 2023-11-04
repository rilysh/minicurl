#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <stdexcept>

// Namespace for general exceptions
namespace MiniCurlException {

template <typename T>
inline void if_return_unavailable(
	const T ret, const std::string fn)
{
	if (!ret)
		throw std::runtime_error("error: when calling " + fn);
}

template <typename T>
inline void if_argument_unavailable(
	const T arg, const std::string error)
{
	if (!arg)
		throw std::runtime_error("error: " + error);
}

};

#endif

