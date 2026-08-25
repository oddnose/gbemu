cmake_minimum_required(VERSION 2.6.0)

project(gbemu C)

set(C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES 
	src/op/op_lookup.c
	src/op/load_instructions.c
	src/op/alu_instructions.c
	src/op/cb_lookup.c
	src/op/rotate_instructions.c
	src/op/branch_instructions.c
	src/state.c
	src/main.c
)

include_directories(src)

add_executable(gbemu ${SOURCE_FILES})

