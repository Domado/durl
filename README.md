# durl (Daiso-URL)

🌩 **durl** is a high-speed, advanced, cross-platform HTTP request library written in C, created by Daiso. It is designed for developers who need lightweight and efficient network communication in C-based projects, supporting multiple platforms with minimal dependencies.

---

## Features

* **Cross-Platform:** Works on Windows, macOS, and Linux.
* **High Performance:** Optimized for speed and low memory usage.
* **Lightweight:** Minimal overhead, easy to integrate into existing projects.
* **Extensible:** Simple structure that allows easy modification and extension.
* **C Language Implementation:** Fully implemented in C for maximum compatibility and control.
* **Synchronous & Asynchronous Requests:** Designed to handle both blocking and non-blocking HTTP operations.

---

## Building

To build `durl` from source, simply run:

```bash
make
```

This will compile the main binary and library files. Ensure you have a standard C compiler installed (e.g., `gcc` or `clang`) and `make`.

### Platform Notes

* **Linux/macOS:** `make` should work out-of-the-box.
* **Windows:** Consider using WSL, MinGW, or Cygwin for building with `make`.

---

## Usage

Currently, `durl` does not have a fully documented API. Developers are encouraged to explore:

* `main.c` for example usage.
* `lib/` directory for function implementations and structures.

Typical usage patterns include:

1. Initializing the request.
2. Setting URL, headers, and request method.
3. Sending the request and reading the response.
4. Handling errors and response codes.

Example snippet:

```c
#include "durl.h"

int main() {
    DURLRequest req;
    durl_init(&req);

    durl_set_url(&req, "http://example.com");
    durl_set_method(&req, "GET");

    if (durl_send(&req) == DURL_OK) {
        printf("Response: %s\n", durl_get_response(&req));
    }

    durl_cleanup(&req);
    return 0;
}
```

---

## License

`durl` is distributed under the **MIT License**, allowing free use, modification, and distribution.

---

## Notes

* No official releases are currently published; cloning the repository is required.
* Primary languages used: **C** and **Makefile**.
* Minimal documentation; reviewing source files is recommended to understand function calls and integration.
* Designed with simplicity in mind to allow developers to adapt it to custom needs.

---

## Recommended Improvements

* Provide full examples for GET, POST, and other HTTP methods.
* Add detailed API documentation for all functions and structures.
* Include platform-specific build instructions.
* Document error handling strategies and possible return codes.
* Add concurrency support for asynchronous requests.
* Include benchmark tests to demonstrate performance advantages.

---

## Contributing

Contributions are welcome! Suggested contributions include:

* Improving documentation.
* Adding new features (e.g., HTTPS, cookies, authentication).
* Optimizing performance.
* Adding more examples and tutorials.

---

## References

* Check the `lib/` directory for implementation details.
* Review `main.c` for basic usage patterns.
* For advanced networking features, understanding the C socket API may be beneficial.
