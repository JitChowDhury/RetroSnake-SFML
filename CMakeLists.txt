#Minimum version required
cmake_minimum_required(VERSION 3.28) 
#project name and language
project(SnakeGame LANGUAGES CXX)
#whre to put the final program the place where cmake doing all the job
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##go to github download the version and no need to download entire history
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)##now we've downloaded sfml and make it ready to use in my project

# ✅ Define the executable
file(GLOB SRC_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)

add_executable(snake ${SRC_FILES} ${HEADER_FILES})

target_include_directories(snake PRIVATE include)
target_compile_features(snake PRIVATE cxx_std_17) ##make sure its build using standard cpp 17


target_link_libraries(snake PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)##connect it to the tools

# Copy SFML DLLs after build (Windows only)
if(WIN32)
    add_custom_command(TARGET snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:sfml-graphics> $<TARGET_FILE_DIR:snake>
    )
endif()

if(MSVC)
    target_compile_options(snake PRIVATE /W4)
else()
    target_compile_options(snake PRIVATE -Wall -Wextra -Wpedantic)
endif()
