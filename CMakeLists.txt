cmake_minimum_required(VERSION 3.16)

project(Arbitrary-Calc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Arbitrary-Calc main.cpp


    tokenizer.h
    tokenizer.cpp
    utils.h
    utils.cpp

    ArbitraryPrecisionCalculator.h
    ArbitraryPrecisionCalculator.cpp
)

include(GNUInstallDirs)
install(TARGETS Arbitrary-Calc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
