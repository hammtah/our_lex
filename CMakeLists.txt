cmake_minimum_required(VERSION 4.0)
project(our_lex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(our_lex
        lex.h
        lexx.c
        utility.h
        states.h)
