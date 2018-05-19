#pragma once

#if defined(WINDOWS)
#include "win32/network.h"
#elif defined(LINUX)
#include "not-win32/network.h"
#endif