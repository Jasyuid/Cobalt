#pragma once

// Standard Library
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <ctime>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <vector>
#include <unordered_map>
#include <unordered_set>

// Platform specific
#ifdef CB_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

// GLM
#include <glm/glm.hpp>
#include <glm/common.hpp>

// Project Core
#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Logger.h"