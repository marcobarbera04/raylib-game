cmake_minimum_required(VERSION 3.10.0)

project(GameProject)

set(CMAKE_C_STANDARD 99)

# Include directories for source code
include_directories(include src)

# Take all .c file in the src folder
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(Game ${SOURCES})

# Link the raylib library
if(WIN32)       # Compile on Windows
    target_link_libraries(Game ${CMAKE_SOURCE_DIR}/lib/libraylib.a opengl32 gdi32 winmm)
elseif(UNIX)    # Compile on Linux
    target_link_libraries(Game ${CMAKE_SOURCE_DIR}/lib/librarylib.a GL X11 pthread)
endif()

# Copy config.txt in the build folder
configure_file(${CMAKE_SOURCE_DIR}/config.txt ${CMAKE_BINARY_DIR}/config.txt COPYONLY)