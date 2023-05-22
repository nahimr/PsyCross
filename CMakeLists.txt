cmake_minimum_required(VERSION 3.6)

project(PsyCross C CXX)

if(ANDROID)
	# FindOpenAL variables
	set(OPENAL_INCLUDE_DIR dependencies/openal/include)
	set(OPENAL_LIBRARY dependencies/openal)
	
	# Build SDL2 from source
	include_directories(dependencies/SDL/include)
	add_subdirectory(dependencies/SDL EXCLUDE_FROM_ALL)
	
	# Build OpenAL from source
	add_subdirectory(${OPENAL_LIBRARY})
	include_directories(${OPENAL_INCLUDE_DIR})
else()
	find_package(SDL2 REQUIRED)
	find_package(OpenAL REQUIRED)
endif()

# Compiler arguments
add_compile_options(
	-Wno-narrowing 
	-Wno-endif-labels 
	-Wno-write-strings 
	-Wno-format 
	-Wno-format-security 
	-Wno-unused-result 
	-fpermissive
)

# Project Files

file(GLOB_RECURSE PSYCROSS_SRCS_C
	"src/*.c"
)

file(GLOB_RECURSE PSYCROSS_SRCS_CPP
	"src/*.cpp"
)

set_source_files_properties(${PSYCROSS_SRCS_C} PROPERTIES LANGUAGE C)
set_source_files_properties(${PSYCROSS_SRCS_CPP} PROPERTIES LANGUAGE CXX)

add_library(psycross_static STATIC ${PSYCROSS_SRCS_C} ${PSYCROSS_SRCS_CPP})
set_target_properties(psycross_static PROPERTIES OUTPUT_NAME "psycross")
target_include_directories(psycross_static PUBLIC "include" "include/psx")

target_link_libraries(psycross_static ${SDL2_LIBRARIES})
target_include_directories(psycross_static PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(psycross_static OpenAL)
target_include_directories(psycross_static PRIVATE ${OpenAL_BINARY_DIR} ${OpenAL_SOURCE_DIR}/include)
