# mini cmake-cache parser

Minimal header-only C++ library for parsing `CMakeCache.txt`-like syntax.

## Features

- Header-only
- Minimal dependencies
- Parses `KEY:TYPE=value` entries
- Lightweight API

## Usage

This library intentionally stays minimal and parses from a string buffer.

```cpp
// Load file contents into std::string fileContents

auto cache = CMakeCacheParse::parse(fileContents);

auto compiler =
    cache["CMAKE_CXX_COMPILER"]->fetch();
```

## Notes

- `fetch()` currently returns `std::string` ONLY!
- Editing/writing cache files is not supported
- This project focuses only on parsing and data access
- The API may change as the project evolves

## License

This project is licensed under CC0-1.0 (public domain dedication)

You are free to use, modify, distribute, and *sublicense* this software without attribution.
