cmake_minimum_required(VERSION 3.11 FATAL_ERROR) # need for FetchContent
project(hw11_sql_server)

set(GCC_LIKE_CXX $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall -Wextra -pedantic -Werror>)
set(MSVC_CXX $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:-W4>)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(Boost_USE_STATIC_LIB OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Threads)
find_package(Boost 1.71.0 REQUIRED
    COMPONENTS system filesystem)

# see https://www.sqlite.org/howtocompile.html
include(FetchContent)
FetchContent_Declare(sqlite3 URL "https://www.sqlite.org/snapshot/sqlite-snapshot-202205041843.tar.gz")
FetchContent_MakeAvailable(sqlite3)
if (NOT sqlite3_POPULATED)
  FetchContent_Populate(sqlite3)
endif()

add_executable(
    join_server
    server.cpp
    connection.cpp
    app.cpp
    commands.cpp
    commands_factory.cpp
    reader.cpp
    main.cpp
    "${sqlite3_SOURCE_DIR}/sqlite3.c")

target_include_directories(join_server
    PUBLIC "${sqlite3_SOURCE_DIR}"
    PUBLIC "${Boost_INCLUDE_DIRS}")

set_target_properties(join_server PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON)

target_link_libraries(
    join_server
    ${CMAKE_THREAD_LIBS_INIT}
    dl)

