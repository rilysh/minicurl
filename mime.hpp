#ifndef MINICURL_MIME_HPP
#define MINICURL_MIME_HPP

#include <curl/curl.h>

#include "except.hpp"

// This namespace implements as libcurl's mime interface as of a wrapper.
namespace MiniCurlMime {

[[nodiscard]]
inline curl_mimepart *addpart(curl_mime *mime)
{
	return curl_mime_addpart(mime);
}

inline CURLcode data(
	curl_mimepart *part, const std::string data,
	size_t data_size)
{
	return curl_mime_data(part, data.c_str(), data_size);
}

inline CURLcode data_cb(
	curl_mimepart *part, curl_off_t data_size,
	curl_read_callback r, curl_seek_callback s,
	curl_free_callback f, void *arg)
{
	MiniCurlException::if_mul_argument_unavailable(r, s, f);
	MiniCurlException::if_argument_unavailable(r, "curl_read_callback");
	MiniCurlException::if_argument_unavailable(s, "curl_seek_callback");
	MiniCurlException::if_argument_unavailable(f, "curl_free_callback");
	MiniCurlException::if_argument_unavailable(arg, "missing argument");

	return curl_mime_data_cb(part, data_size, r, s, f, arg);
}

inline CURLcode encoder(curl_mimepart *part, const std::string encoding)
{
	return curl_mime_encoder(part, encoding.c_str());
}

inline CURLcode filedata(curl_mimepart *part, const std::string filename)
{
	return curl_mime_filedata(part, filename.c_str());
}

inline void free(curl_mime *mime)
{
	curl_mime_free(mime);
}

inline CURLcode headers(
	curl_mimepart *part, struct curl_slist *headers,
	int ownership)
{
	return curl_mime_headers(part, headers, ownership);
}

[[nodiscard]]
inline curl_mime *init(CURL *curl)
{
	return curl_mime_init(curl);
}

inline CURLcode name(curl_mimepart *part, const std::string str)
{
	return curl_mime_name(part, str.c_str());
}

inline CURLcode subparts(curl_mimepart *part, curl_mime *subp)
{
	return curl_mime_subparts(part, subp);
}

inline CURLcode type(curl_mimepart *part, const std::string mime_type)
{
	return curl_mime_type(part, mime_type.c_str());
}

};
#endif
