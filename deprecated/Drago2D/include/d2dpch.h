#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>
#include <numeric>
#include <atomic>
#include <bitset>
#include <cstdint>

#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <fstream>
#include <optional>
#include <variant>

/* #undef D2D_PLATFORM_WINDOWS */
#ifdef D2D_PLATFORM_WINDOWS
    #include <Windows.h>
#else
    #include <unistd.h>
#endif
