cmake_minimum_required(VERSION 3.6)

project(PsyCross C CXX)

option(BUILD_DEPS "Building Dependencies from sources" OFF)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(PSYCROSS_SUBPROJECT OFF)
else()
  set(PSYCROSS_SUBPROJECT ON)
endif()

set(LD_LIBS OpenAL)

# Building from sources
if(BUILD_DEPS)
	if(NOT(PSYCROSS_SUBPROJECT))
		# Dependencies Sources
		set(OPENAL_LIBRARY dependencies/openal)
		set(SDL2_LIBRARY dependencies/SDL)
	endif()

	if(NOT(OPENAL_LIBRARY))
		message(FATAL_ERROR "OPENAL_LIBRARY is missing !")
	endif()

	if(NOT(SDL2_LIBRARY))
		message(FATAL_ERROR "SDL2_LIBRARY is missing !")
	endif()

	# Dependencies Includes
	set(OPENAL_INCLUDE_DIR ${OPENAL_LIBRARY}/include)
	set(SDL2_INCLUDE_DIR ${SDL2_LIBRARY}/include)

	# Build SDL2 from source
	add_subdirectory(${SDL2_LIBRARY})
	include_directories(${SDL2_INCLUDE_DIR})

	# Build OpenAL from source
	add_subdirectory(${OPENAL_LIBRARY})
	include_directories(${OPENAL_INCLUDE_DIR})
elseif(UNIX AND NOT(ANDROID OR EMSCRIPTEN OR IOS OR TVOS))
	find_package(SDL2 REQUIRED)
	find_package(OpenAL REQUIRED)
	set(LD_LIBS openal)

	if(NOT(OPENAL_FOUND))
		message(FATAL_ERROR "Missing OpenAL !")
	endif()

	if(NOT(SDL2_FOUND))
		message(FATAL_ERROR "Missing SDL2 !")
	endif()
endif()

if(WIN32)
	add_definitions(-D_WINDOWS)
elseif(EMSCRIPTEN)
	add_definitions(-D__EMSCRIPTEN__)
	add_compile_options(
		-Wno-c++11-narrowing
		-Wno-constant-conversion
		-Wno-writable-strings
		-Wno-unused-value
		-Wno-switch
		-Wno-shift-op-parentheses
		-Wno-parentheses
		-Wno-format
	)
elseif(UNIX)
	add_compile_options(
		-Wno-narrowing 
		-Wno-endif-labels 
		-Wno-write-strings 
		-Wno-format 
		-Wno-format-security 
		-Wno-unused-result 
		-fpermissive
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(
        -D_DEBUG=1
    )
endif()

# Project Files
file(GLOB_RECURSE PSYCROSS_SRCS_C "src/**/*.c" "src/**/*.C")
file(GLOB_RECURSE PSYCROSS_SRCS_CPP "src/**.cpp" "src/**.CPP")

set_source_files_properties(${PSYCROSS_SRCS_C} PROPERTIES LANGUAGE C)
set_source_files_properties(${PSYCROSS_SRCS_CPP} PROPERTIES LANGUAGE CXX)

add_library(PsyCross STATIC ${PSYCROSS_SRCS_C} ${PSYCROSS_SRCS_CPP})
set_target_properties(PsyCross PROPERTIES OUTPUT_NAME "psycross")
target_include_directories(PsyCross PUBLIC "include" "include/psx")

target_include_directories(PsyCross PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(PsyCross ${SDL2_LIBRARIES})

target_include_directories(PsyCross PRIVATE ${OpenAL_BINARY_DIR} ${OpenAL_SOURCE_DIR}/include)
target_link_libraries(PsyCross ${LD_LIBS})
