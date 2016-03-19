cmake_minimum_required(VERSION 3.3)
project(synthesizer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    operations/AddOp.h
    operations/GreaterThanOp.h
        operations/primitive/IdentityOp.h
    operations/IntEqualsOp.h
    operations/LessThanOp.h
    operations/MultiplyOp.h
    operations/Operation.h
        operations/primitive/SelectorOp.h
    programs/Program.h
    programs/Program.hpp
    main.cpp
    ProgramContainer.h
    ProgramContainer.hpp
    Synthesizer.h
    Synthesizer.hpp
    Type.h
    utils/util.h userDefinedTypes/List.hpp operations/ListAddItemOp.h operations/TernaryOp.h)

add_executable(synthesizer ${SOURCE_FILES})