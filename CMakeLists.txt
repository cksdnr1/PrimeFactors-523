cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 사용되는 언어를 설정합니다.
project(MyProject VERSION 1.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_COVERAGE "Enable coverage reporting" ON)

if (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Coverage enabled")

    set(COVERAGE_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COVERAGE_FLAGS}")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES "./src/*.cpp")
file(GLOB DIP "./DIP/*.cpp")
file(GLOB OCP "./OCP/*.cpp")
file(GLOB ISP "./ISP/*.cpp")
file(GLOB SRP "./SRP/*.cpp")
file(GLOB TEST "./test/*.cpp")

add_library(Core
    ${SOURCES}
)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 실행 파일을 생성합니다.
add_executable(MyProject main.cpp)

# 실행 파일을 생성합니다.
add_executable(Test ${TEST})

# 디버깅을 위한 설정 (선택 사항)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(MyProject PRIVATE Core gmock_main)

# GTest와 연결
target_link_libraries(Test PRIVATE Core gtest_main gmock_main)

enable_testing()
add_test(NAME my_test COMMAND Test)