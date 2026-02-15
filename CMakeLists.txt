cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(OBJC)

project(vulkanengine DESCRIPTION "vulkanengine" LANGUAGES CXX OBJC)
file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
)
add_executable(${PROJECT_NAME})

set(ENABLE_SSE2 True)
set(ENABLE_AVX2 True)

#####################


# specify the C++ standard
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)


# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# grant IEEE 754 compliance
	target_compile_options(${PROJECT_NAME} PUBLIC "/fp:strict")
	# use intrinsic functions
	target_compile_options(${PROJECT_NAME} PUBLIC "/Oi")
	# set target architecture
	if(ENABLE_AVX2)
		target_compile_options(${PROJECT_NAME} PUBLIC "/arch:AVX2")
	elseif(ENABLE_SSE2)
		target_compile_options(${PROJECT_NAME} PUBLIC "/arch:SSE2")
	endif()
	# reserve enough stack size
	target_link_options(${PROJECT_NAME} PUBLIC "/STACK:8421376")
	# turn off annoying warnings
	target_compile_options(${PROJECT_NAME} PUBLIC "/D _CRT_SECURE_NO_WARNINGS")
else()
	# set standard optimization level
	target_compile_options(${PROJECT_NAME} PUBLIC -O0)
	# reserve enough stack size	
	target_compile_options(${PROJECT_NAME} PUBLIC -Wl,-z,stacksize=8421376)
	# grant IEEE 754 compliance
	target_compile_options(${PROJECT_NAME} PUBLIC -frounding-math)
	# set target architecture
	if(ENABLE_AVX2)
		target_compile_options(${PROJECT_NAME} PUBLIC "-mavx2")
  		target_compile_options(${PROJECT_NAME} PUBLIC "-mfma")
	elseif(ENABLE_SSE2)
		target_compile_options(${PROJECT_NAME} PUBLIC "-msse2")
	endif()
endif()




find_package(Vulkan REQUIRED)

add_subdirectory(deps/glfw)
#add_subdirectory(deps/geogram)
add_subdirectory(deps/glm)
include_directories(deps/glm)
add_subdirectory(deps/tinyobjloader)
# The one below is a single file external header library
include_directories(deps/stbimage) 
# adding tinybvh
include_directories(deps/tinybvh)

#STL library
add_subdirectory(deps/openstl)

#Indirect Predicates
#include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/deps/IndirectPredicates/include)


# For IMGUI, the recommended method is to just include imgui .cpp files in your target like your own source files
set(IMGUI_DIR deps/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_sources(${PROJECT_NAME} PUBLIC ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp)

#geometry-central
#add_subdirectory(deps/geometry-central)

#libcifpp for parsing protein files
#add_subdirectory(deps/libcifpp-7.0.9)

#add_subdirectory(deps/gemmi-0.7.3 EXCLUDE_FROM_ALL)
#include_directories(deps/gemmi-0.7.3/include)

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include  ${CMAKE_CURRENT_SOURCE_DIR}/include/vulkanengine ${CMAKE_CURRENT_SOURCE_DIR}/include/window)

# Get the list of include directories for the current directory
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

# Print each directory
foreach(dir ${dirs})
  message(STATUS "Include directory: ${dir}")
endforeach()




# Final compilation and linking
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw ${GLFW_LIBRARIES} Vulkan::Vulkan tinyobjloader openstl_core)
#target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)


#add_subdirectory(examples/inthomog)
#add_subdirectory(examples/vkcheck)

#GTest and GMock
#include(cmake/tests.cmake)
#include_directories(/Users/sharmh15/projectsPersonal/googletest-1.16.0/install/include)
#include_directories(/Users/sharmh15/projectsPersonal/googletest-1.16.0/install/include/gmock)
#link_directories(/Users/sharmh15/projectsPersonal/googletest-1.16.0/install/lib)
#enable_testing()
#add_subdirectory(tests)
