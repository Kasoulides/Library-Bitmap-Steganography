cmake_minimum_required(VERSION 3.17)
project(EPL232_HW4 C)

set(CMAKE_C_STANDARD 99)

add_library(bmplib bmp.c bmp.h grayscale.c grayscale.h list.c list.h stringToImage.c stringToImage.h encodeStegano.c encodeStegano.h decodeStegano.c decodeStegano.h ImageToString.c ImageToString.h encodeText.c encodeText.h decodeText.c decodeText.h )
add_executable(EPL232_HW4 bmpSteganography.c $<TARGET_OBJECTS:bmplib>)

