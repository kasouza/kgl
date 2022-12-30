file(COPY ${PROJECT_SOURCE_DIR}/src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
	main.c
)

set(TEST_EXEC_NAME test_${PROJECT_NAME})

add_executable(${TEST_EXEC_NAME} ${SOURCES})

target_compile_features(${TEST_EXEC_NAME} PUBLIC c_std_17)
target_link_libraries(${TEST_EXEC_NAME} PUBLIC kgl)
target_compile_options(${TEST_EXEC_NAME} PRIVATE ${COMPILE_OPTIONS})
