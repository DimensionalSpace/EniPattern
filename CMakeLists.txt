cmake_minimum_required(VERSION 3.21)
project(EniPattern LANGUAGES CXX)

include(FetchContent)
set(SFML_BUILD_NETWORK OFF)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(EniPattern src/Main.cpp)
target_link_libraries(EniPattern PRIVATE sfml-graphics sfml-audio)
target_compile_features(EniPattern PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET EniPattern POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:EniPattern> $<TARGET_FILE_DIR:EniPattern> COMMAND_EXPAND_LISTS)
endif()
if(WIN32)
add_custom_command(
        TARGET EniPattern
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:EniPattern>
        VERBATIM)
endif()
install(TARGETS EniPattern)
