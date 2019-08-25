cmake_minimum_required(VERSION 3.4.1)

add_library(
        SystemPropertiesUtils
        SHARED
        src/main/cpp/system_properties_utils.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        SystemPropertiesUtils
        ${log-lib}
)