cmake_minimum_required(VERSION 3.5)
#	set standard required to ensure that you get 
#	the same version of C++ on every platform
#	as some environments default to older dialects 
#	of C++ and some do not.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "jsonc++")

message("**")
message("** PROJECT_NAME....: ${PROJECT_NAME}")
message("**")

project (${PROJECT_NAME})

add_subdirectory(src)
