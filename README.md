# Asio Extensions (_AsioExt_)

[![Build Status](https://travis-ci.org/timniederhausen/asio-extensions.svg?branch=master)](https://travis-ci.org/timniederhausen/asio-extensions)
[![Build status](https://ci.appveyor.com/api/projects/status/696yog08f0fbpck0/branch/master?svg=true)](https://ci.appveyor.com/project/timniederhausen/asio-extensions/branch/master)

## Feature overview

* Wrappers around native file handles with support for asio's `*Stream` concepts.
  (`asioext::file_handle` and `asioext::scoped_file_handle`).
* Asynchronous file I/O (`asioext::basic_file`).
  Currently only a thread(-pool) service is implemented
  (`asioext::thread_pool_file_service`).
* Utilities for reading/writing files:
  * `asioext::read_file`
  * `asioext::write_file`
* Utilities for service/custom I/O object writers.

AsioExt is compatible with standalone Asio, as well as the Boost version.
To use the Boost version, #define ``ASIOEXT_USE_BOOST_ASIO``.

## Building

AsioExt requires at least a C++03-compliant compiler.
Not all AsioExt features are usable from C++03 though
(e.g. movable `scoped_file_handle` objects).
These features are enabled based on the C++11/C++14 support of the used compiler.

Currently, AsioExt is being tested with the following compilers:

* GCC 4.8
* Clang 3.6
* MSVC 2015

Like Asio, AsioExt is header-only by default.
However, it is also possible to build the AsioExt library as a separate compilation unit.

## Library dependencies:

* Asio 1.10.0+ (Only if not using Boost.Asio)
* [optional] Boost 1.46.0+ (If _Boost.Filesystem_ support is enabled)

## Simple example

```cpp
#include <asioext/scoped_file_handle.hpp>
#include <asioext/read_file.hpp>
#include <asioext/write_file.hpp>
#include <asioext/open_flags.hpp>

#include <asio/read.hpp>

#include <iostream>
#include <cassert>

int main(int argc, const char* argv[])
{
  const std::string test_content = "Hello world";

  try {
    // Utility functions write/read containers and buffer sequences to/from files.
    const std::array<asio::const_buffer, 2> buffers_to_write = {
      asio::buffer(test_content),
      asio::buffer(test_content),
    };
    asioext::write_file("myfile.txt", buffers_to_write);

    std::string read_content;
    asioext::read_file("myfile.txt", read_content);

    assert(read_content == test_content + test_content);

    // (scoped_)file_handle provides low-level access to files.
    // (There's also basic_file, which needs an asio::io_service and provides
    // asynchronous I/O.)
    asioext::scoped_file_handle file("myfile.txt",
                                     asioext::access_read |
                                     asioext::open_existing);

    assert(file.size() == test_content.size() * 2);

    std::string read_content2(test_content.size(), '\0');
    asio::read(file, asio::buffer(&read_content2[0], read_content2.size()));

    assert(read_content2 == test_content);
    return 0;
  } catch (std::exception& e) {
    // Exceptions are used for error reporting here.
    // All functions also offer a non-throwing overload,
    // which takes an asio::error_code& instead.
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }
}
```

Take a look at the [examples directory](example) for more!

## Documentation

The documentation can be found at http://timniederhausen.github.io/asio-extensions,
or inside the `gh-pages` branch.

Additionally, the documentation can be generated by building the special
`asioext.doc` target. Note that this target is only available if you have
[Doxygen](http://www.stack.nl/~dimitri/doxygen/) installed.

## License

Please see [LICENSE_1_0.txt](LICENSE_1_0.txt).
