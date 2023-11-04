#ifndef MINICURL_GLOBAL_HPP
#define MINICURL_GLOBAL_HPP

#include <curl/curl.h>

#include "except.hpp"

// This namespace implements as libcurl's global interface as of a wrapper.
namespace MiniCurlGlobal {

inline void cleanup()
{
	curl_global_cleanup();
}

inline CURLcode init(long flags)
{
	return curl_global_init(flags);
}

inline CURLcode init_mem(
	long flags, curl_malloc_callback m,
	curl_free_callback f, curl_realloc_callback r,
	curl_strdup_callback s, curl_calloc_callback c)
{
	MiniCurlException::if_argument_unavailable(m, "curl_malloc_callback");
	MiniCurlException::if_argument_unavailable(f, "curl_free_callback");
	MiniCurlException::if_argument_unavailable(r, "curl_realloc_callback");
	MiniCurlException::if_argument_unavailable(s, "curl_strdup_callback");
	MiniCurlException::if_argument_unavailable(c, "curl_calloc_callback");

	return curl_global_init_mem(flags, m, f, r, s, c);
}

};

#endif
