set(SOURCES
	error.c
	input.c
	renderer.c
	shaders.c
	utils.c
)

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad stb_image)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
