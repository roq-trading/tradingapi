set(TARGET_NAME "${PROJECT_NAME}-test")

set(SOURCES
    alignment.cpp
    chrono.cpp
    compare.cpp
    exceptions.cpp
    format.cpp
    mask.cpp
    metrics.cpp
    safe_cast.cpp
    span.cpp
    string_buffer.cpp
    traits.cpp
    update.cpp
    utils.cpp
    main.cpp)

add_executable("${TARGET_NAME}" ${SOURCES})

# dependencies

add_dependencies(${TARGET_NAME} ${PROJECT_NAME}-include-cpp)
add_dependencies(${TARGET_NAME} ${PROJECT_NAME}-include-fbs)

# target

target_link_libraries("${TARGET_NAME}" fmt::fmt gtest_main)

target_compile_features("${TARGET_NAME}" PUBLIC cxx_std_17)

# run

add_test(NAME "${TARGET_NAME}" COMMAND "${TARGET_NAME}")
