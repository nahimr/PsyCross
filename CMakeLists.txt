cmake_minimum_required(VERSION 3.6)

project(PsyCross C CXX)

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

add_subdirectory(dependencies/SDL)
add_subdirectory(dependencies/openal)

# Project Files

file(GLOB_RECURSE PSYCROSS_SRCS_C
	"*.c"
)

file(GLOB_RECURSE PSYCROSS_SRCS_CPP
	"*.cpp"
)

# SDL2 Variables

set(SDL2_BINDIR "${SDL2_DIR}/bin")

set_source_files_properties(${PSYCROSS_SRCS_C} PROPERTIES LANGUAGE C)
set_source_files_properties(${PSYCROSS_SRCS_CPP} PROPERTIES LANGUAGE CXX)

add_library(psycross_static STATIC ${PSYCROSS_SRCS_C} ${PSYCROSS_SRCS_CPP})
set_target_properties(psycross_static PROPERTIES OUTPUT_NAME "psycross")
target_include_directories(psycross_static PUBLIC "include" "include/psx")

find_package(SDL2 REQUIRED)
target_link_libraries(psycross_static ${SDL2_LIBRARIES})
target_include_directories(psycross_static PRIVATE ${SDL2_INCLUDE_DIRS})

find_package(OpenAL REQUIRED)
target_link_libraries(psycross_static OpenAL)
target_include_directories(psycross_static PRIVATE ${OpenAL_BINARY_DIR} ${OpenAL_SOURCE_DIR}/include)
