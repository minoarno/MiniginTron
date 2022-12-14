#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push)
#pragma warning(disable : 4189)
#pragma warning(disable : 4201)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)
#include <glm/glm.hpp>
#include <SDL.h>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_plot.h"

#pragma warning (pop)

#include "Log.h"
#include "Box2D.h"