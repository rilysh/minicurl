#ifndef MINICURL_MULTI_HPP
#define MINICURL_MULTI_HPP

#include <curl/curl.h>

// This namespace implements as libcurl's multi interface as of a wrapper.
namespace MiniCurlMulti {

inline CURLMcode add_handle(CURLM *multi, CURL *easy)
{
	return curl_multi_add_handle(multi, easy);
}

inline CURLMcode assign(
	CURLM *multi, curl_socket_t sockfd, void *sock_ptr)
{
	return curl_multi_assign(multi, sockfd, sock_ptr);
}

inline CURLMcode cleanup(CURLM *multi)
{
	return curl_multi_cleanup(multi);
}

inline CURLMcode fdset(
	CURLM *multi, fd_set *r, fd_set *w,
	fd_set *e, int *max_fds)
{
	return curl_multi_fdset(multi, r, w, e, max_fds);
}

[[nodiscard]]
inline CURLM *init()
{
	auto multi = curl_multi_init();
	MiniCurlException::if_return_unavailable(multi, "curl_multi_init()");
	return multi;
}

inline CURLMcode perform(CURLM *multi, int *handles)
{
	return curl_multi_perform(multi, handles);
}

inline CURLMcode remove_handle(CURLM *multi, CURL *easy)
{
	return curl_multi_remove_handle(multi, easy);
}

template <typename... Args>
inline CURLMcode setopt(CURLM *multi, CURLMoption option, Args&&... args)
{
	return curl_multi_setopt(multi, option, args...);
}

inline CURLMcode socket_action(
	CURLM *multi, curl_socket_t sockfd,
	int ev_bit_mask, int *handles)
{
	return curl_multi_socket_action(multi, sockfd, ev_bit_mask, handles);
}

[[nodiscard]]
inline const std::string strerror(CURLMcode error)
{
	return curl_multi_strerror(error);
}

inline CURLMcode timeout(CURLM *multi, long *timeout)
{
	return curl_multi_timeout(multi, timeout);
}

inline CURLMcode poll(
	CURLM *multi, struct curl_waitfd extra_fds[],
	unsigned int extra_nfds, int timeout_ms,
	int *numfds)
{
	return curl_multi_poll(
		multi, extra_fds, extra_nfds,
		timeout_ms, numfds);
}

inline CURLMcode wait(
	CURLM *multi, struct curl_waitfd extra_fds[],
	unsigned int extra_nfds, int timeout_ms,
	int *numfds)
{
	return curl_multi_wait(
		multi, extra_fds, extra_nfds,
		timeout_ms, numfds);
}

inline CURLMcode wakeup(CURLM *multi)
{
	return curl_multi_wakeup(multi);
}

};
#endif
