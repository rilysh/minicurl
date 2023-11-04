## minicurl
minicurl is a tiny wrapper around libcurl for C++

### Features
1. It's small! Smaller than cURLpp.
2. Less layers of abstraction, so less overhead.
3. It's just libcurl with fancy wrapping.
4. Supports C++11 and later.

### Example
```cpp
#include <iostream>

#include "easy.hpp"

void make_request(const std::string url)
{
	std::string chunk;

	const auto curl = MiniCurlEasy::init();
	if (curl) {
		// Variadic arguments don't know the "real" type,
		// so we've to explicitly make it a const char *
		MiniCurlEasy::setopt(curl, CURLOPT_URL, url.c_str());
		MiniCurlEasy::setopt(curl, CURLOPT_WRITEFUNCTION, MiniCurlEasy::write_memory_cb);
		MiniCurlEasy::setopt(curl, CURLOPT_WRITEDATA, &chunk);

		const auto ret = MiniCurlEasy::perform(curl);
		if (ret != CURLE_OK)
			throw std::runtime_error(
				"MiniCurlEasy::perform() failed, reason: "
				+ MiniCurlEasy::strerror(ret));

		if (url.find_first_of("colepaws"))
				std::cout << chunk
					.replace(0, 3, "")
					.replace(2, 5, "") << '\n';
			else
				std::cout << chunk << '\n';

		MiniCurlEasy::cleanup(curl);
	}
};

int main()
{
	make_request("https://colepaws.pet");
	make_request("https://example.com");
}
```

### Donate
BTC: `bc1qn6xu7hlzx94np2u3xs7tgq8uztamrhdh5gv87t`
