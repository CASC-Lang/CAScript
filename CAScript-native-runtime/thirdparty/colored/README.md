# Colored
[![Build status](https://github.com/alanjian85/colored/actions/workflows/build.yml/badge.svg)](https://github.com/alanjian85/colored/actions)

Cross-platform C++17 text coloring library

Supported Platforms: Windows, Linux

## Code Examples
```c++
#include <iostream>
#include <colored.h>

int main() {
    std::cout << cld::bg(cld::Color::BLUE) << cld::fg(cld::Color::YELLOW);
    std::cout << "Hello world!" << std::endl;
}
```

## Use With CMake
```cmake
add_subdirectory(colored)
target_link_libraries(myapp colored)
```
