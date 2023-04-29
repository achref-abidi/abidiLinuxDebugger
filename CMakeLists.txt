##
## TopLevel Cmake file
##
###

cmake_minimum_required(VERSION 3.21)

##
## PROJECT
## name and version
##
set(VERSION 0.1)
project(alDbg)

##
## CONFIGS
## The compiled binaries will reside inside out/bin inside the binaryDir set in CMakePresets.json 
##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/out/bin)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,modernize-*")

##
## OPTIONS
##
##
set(BUILD_SAMPLES ON CACHE INTERNAL "Building samples to test debugger")

##
## FUNCTION
## Set the PATH to the includes SRC, DIR
##
function(APPEND_FUNC var)
    set(listVar "")
    foreach (f ${${var}})
        list(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
    endforeach (f)
    set(${var} "${listVar}" PARENT_SCOPE)  #< why parent_scope is needed here
endfunction()


##
## DEPENDENCIES
## adding external projects
##
add_subdirectory(dependencies)

##
## SUB-PROJECTS
## Sub-directories for this project
##
add_subdirectory(Foundation)
if( BUILD_SAMPLES )
    add_subdirectory(samples)
endif()

##
## EXECUTABLE
## Building the debugger
##
add_executable(${PROJECT_NAME} ${ALDBG_SRC} ${LINENOISE_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${LINENOISE_INC_DIR} ${ALDBG_INC})
