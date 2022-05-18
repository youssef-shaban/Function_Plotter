project(Function_lib)

set(HEADER_FILES
        functiongenerator.h
        )

set(SOURCE_FILES
        functiongenerator.cpp
        )

add_library(Function_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})