cmake_minimum_required(VERSION 3.16)
project(sonic_cd_file_tool LANGUAGES CXX)

add_executable(sonic_cd_file_tool
	"source/helpers.cpp"
	"source/main.cpp"
	"source/process.cpp"
	"source/process_europe.cpp"
    "source/process_japan.cpp"
    "source/process_usa.cpp")

set_property(TARGET sonic_cd_file_tool PROPERTY CXX_STANDARD 17)