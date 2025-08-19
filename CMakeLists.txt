cmake_minimum_required(VERSION 3.28)
project(SnakeGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# ✅ Define the executable
add_executable(snake 
    src/main.cpp 
    # src/snake.cpp 
    # src/food.cpp 
    # src/game.cpp
)

target_include_directories(snake PRIVATE include)
target_compile_features(snake PRIVATE cxx_std_17)


target_link_libraries(snake PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

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
