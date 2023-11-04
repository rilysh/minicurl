#ifndef MINICURL_MISC_HPP
#define MINICURL_MISC_HPP

#include <curl/curl.h>

// This namespace implements a few miscellaneous functions.
namespace MiniCurlMisc {

inline const std::string version()
{
	return curl_version();
}

[[nodiscard]]
inline curl_version_info_data *version_info(CURLversion age)
{
	return curl_version_info(age);
}

};

#endif
