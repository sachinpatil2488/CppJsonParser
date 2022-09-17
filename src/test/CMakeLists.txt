# Our target name
set(UNIT_TESTS ${PROJECT_NAME}-test)

set(TEST_SOURCES
        main.cpp
		ParserTest.hpp
        ParserTest.cpp
        )

add_executable(${UNIT_TESTS}
        ${TEST_SOURCES}
        )

target_link_libraries(${UNIT_TESTS}
        ${PROJECT_NAME}-bits
        )

target_include_directories(${UNIT_TESTS} PRIVATE \..)

add_dependencies(${UNIT_TESTS} ${PROJECT_NAME}-bits)

