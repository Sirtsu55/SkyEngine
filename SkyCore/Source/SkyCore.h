#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <unordered_set>
#include <memory>
#include <sstream>
#include <filesystem>



#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>


#include <glad/glad.h>

#include <fxgltf/fxgltf.h>


//stbi
#include <stb_image/stb_image.h>


#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>




//---------------------------------------
//Shared Pointers
//---------------------------------------

template<typename T>
using Sptr = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Sptr<T> CreateSptr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}


//---------------------------------------
//Unique Pointers
//---------------------------------------

template<typename T>
using Uptr = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Uptr<T> CreateUptr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}



//---------------------------------------
//Casting
//---------------------------------------

#define ReCast reinterpret_cast



//---------------------------------------
//Logging
//---------------------------------------

#define LOG 1


#if LOG
#include "Utils/Logger.h"

//CORE LOGGER
#define LOG_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define LOG_ERROR(...)    ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_WARN(...)     ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_INFO(...)     ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...)    ::Log::GetCoreLogger()->trace(__VA_ARGS__)



#endif // LOG


#define PROFILING 1

#if PROFILING
#include "Utils/Timers.h"


#define PROFILE(Name) ScopedTimer Timer##__LINE__(Name)
#define PROFILE_NO_LOG(Name) ScopedTimer Timer##__LINE__(Name, false)

#define PROFILE_FUNCTION() ScopedTimer Timer##__LINE__(__FUNCTION__)
#define PROFILE_FUNCTION_NO_LOG() ScopedTimer Timer##__LINE__(__FUNCTION__, false)

#define PROFILE_FUNCTION_SIG() ScopedTimer Timer##__LINE__(__FUNCSIG__)
#define PROFILE_FUNCTION_SIG_NO_LOG() ScopedTimer Timer##__LINE__(__FUNCSIG__, false)

#else

#define PROFILE(Name) 
#define PROFILE_NO_LOG(Name) 

#define PROFILE_FUNCTION() 
#define PROFILE_FUNCTION_NO_LOG() 

#define PROFILE_FUNCTION_SIG()
#define PROFILE_FUNCTION_SIG_NO_LOG()
#endif // PROFILING












