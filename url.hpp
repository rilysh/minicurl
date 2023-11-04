#ifndef MINICURL_URL_HPP
#define MINICURL_URL_HPP

#include <curl/curl.h>

#include "except.hpp"

// This namespace implements as libcurl's URL interface as of a wrapper.
namespace MiniCurlURL {

[[nodiscard]]
inline CURLU *url()
{
	return curl_url();
}

inline void cleanup(CURLU *url)
{
	curl_url_cleanup(url);
}

[[nodiscard]]
inline CURLU *dup(CURLU *url)
{
	auto obj = curl_url_dup(url);
	MiniCurlException::if_return_unavailable(obj, "curl_url_dup()");
	return obj;
}

inline CURLUcode get(CURLU *url, CURLUPart part,
		     char **content, unsigned int flags)
{
	return curl_url_get(url, part, content, flags);
}

inline CURLUcode set(CURLU *url, CURLUPart part,
		     const std::string content,
		     unsigned int flags)
{
	return curl_url_set(url, part, content.c_str(), flags);
}	

};
#endif
