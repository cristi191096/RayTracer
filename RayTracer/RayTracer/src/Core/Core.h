#pragma once


#define ASSERT(x, ...) { if(!(x)) { ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }