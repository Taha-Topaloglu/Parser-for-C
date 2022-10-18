cmake_minimum_required(VERSION 3.21)
project(MatlangProject C)

set(CMAKE_C_STANDARD 99)

add_executable(MatlangProject main.c stringutils.h stringutils.c definitionstatements.h definitionstatements.c structs.h structs.c assignstatements.c assignstatements.h datastructures.c datastructures.h printstatements.c printstatements.h infixtopostfix.c infixtopostfix.h expressionparsing.c expressionparsing.h indexedassignments.c indexedassignments.h forloops.c forloops.h)
