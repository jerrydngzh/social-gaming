add_library(RPSGame RockPaperScissorsGame.cpp)
target_include_directories(RPSGame PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
