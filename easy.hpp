#ifndef MINICURL_EASY_HPP
#define MINICURL_EASY_HPP

#include <utility>
#include <fstream>

#include <sys/stat.h>
#include <curl/curl.h>

#include "except.hpp"

// This namespace implements as libcurl's easy interface as of a wrapper.
namespace MiniCurlEasy {

inline void cleanup(CURL *easy)
{
	curl_easy_cleanup(easy);
}

[[nodiscard]]
inline CURL *duphandle(CURL *easy)
{
	auto ret = curl_easy_duphandle(easy);
	MiniCurlException::if_return_unavailable(ret, "curl_easy_duphandle()");
	return ret;
}

[[nodiscard]]
inline std::string escape(CURL *easy, const std::string data, int len)
{
	auto ret = curl_easy_escape(easy, data.c_str(), len);
	MiniCurlException::if_return_unavailable(ret, "curl_easy_escape()");
	return ret;
}

template <typename... Args>
inline CURLcode getinfo(CURL *easy, CURLINFO info, const Args&&... args)
{
	return curl_easy_getinfo(easy, info, std::forward(args)...);
}

inline CURLHcode header(
	CURL *easy, const std::string name, size_t index,
	uint32_t origin, int request, struct curl_header *header)
{
	return curl_easy_header(easy, name.c_str(), index, origin, request, &header);
}

[[nodiscard]]
inline CURL *init()
{
	auto easy = curl_easy_init();
	MiniCurlException::if_return_unavailable(easy, "curl_easy_init()");
	return easy;
}

[[nodiscard]]
inline struct curl_header *nextheader(
	CURL *easy, uint32_t origin,
	int request, struct curl_header *pheader)
{
	return curl_easy_nextheader(easy, origin, request, pheader);
}

[[nodiscard]]
inline const struct curl_easyoption *option_by_id(CURLoption id)
{
	const auto opt = curl_easy_option_by_id(id);
	MiniCurlException::if_return_unavailable(opt, "curl_easy_option_by_id()");
	return opt;
}

[[nodiscard]]
inline const struct curl_easyoption *option_by_name(const std::string name)
{
	const auto opt = curl_easy_option_by_name(name.c_str());
	MiniCurlException::if_return_unavailable(opt, "curl_easy_option_by_name()");
	return opt;
}

[[nodiscard]]
inline const struct curl_easyoption *option_next(const struct curl_easyoption *opt)
{
	return curl_easy_option_next(opt);
}

inline CURLcode pause(CURL *easy, int bit_mask)
{
	return curl_easy_pause(easy, bit_mask);
}

inline CURLcode perform(CURL *easy)
{
	return curl_easy_perform(easy);
}

inline CURLcode recv(CURL *easy, void *buffer, size_t buflen, size_t *n)
{
	return curl_easy_recv(easy, buffer, buflen, n);
}

inline void reset(CURL *easy)
{
	curl_easy_reset(easy);
}

inline CURLcode send(
	CURL *easy, const void *buffer,
	size_t buflen, size_t *n)
{
	return curl_easy_send(easy, buffer, buflen, n);
}

template <typename... Args>
inline CURLcode setopt(CURL *easy, CURLoption option, const Args... args)
{
	return curl_easy_setopt(easy, option, args...);
}


[[nodiscard]]
inline const std::string strerror(CURLcode error)
{
	return curl_easy_strerror(error);
}

[[nodiscard]]
inline std::string unescape(
	CURL *easy, const std::string input,
	int in_length, int *out_length)
{
	auto ret = curl_easy_unescape(easy, input.c_str(), in_length, out_length);
	MiniCurlException::if_return_unavailable(ret, "curl_easy_unescape()");
	return ret;
}

inline CURLcode upkeep(CURL *easy)
{
	return curl_easy_upkeep(easy);
}

// Helpers (non-standard) functions
[[nodiscard]]
inline std::FILE *set_file_name(const std::string name, bool read_only)
{
	std::FILE *fp;

	fp = std::fopen(name.c_str(), read_only ? "rb" : "wb");
	if (fp == nullptr)
		return nullptr;

	return fp;
}

[[nodiscard]]
inline std::size_t get_file_size(std::FILE *fp)
{
	struct stat st;

	if (fstat(fileno(fp), &st) != 0)
		return -1;

	return st.st_size;
}
	
[[nodiscard]]
inline std::size_t write_data_cb(void *ptr, std::size_t size, std::size_t nmemb, void *stream)
{
	return std::fwrite(ptr, size, nmemb, static_cast<std::FILE *>(stream));
}

[[nodiscard]]
inline std::size_t write_memory_cb(void* contents, size_t size, size_t nmemb, void* userp)
{
	auto real = size * nmemb;
	auto& mem = *static_cast<std::string *>(userp);
	mem.append(static_cast<char *>(contents), real);

	return real;
}

};

#endif
