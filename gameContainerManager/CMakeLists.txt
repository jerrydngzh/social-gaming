cmake_minimum_required(VERSION 3.20)
project(gameContainerManager) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files 
set(SOURCES 
    main.cpp
    serverProcessor.cpp
)

# Add the header files 
set(HEADERS 
    serverProcessorDTO.h
)

add_executable(main ${SOURCES} ${HEADERS})