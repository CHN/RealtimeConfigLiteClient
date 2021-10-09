project(Sandbox)

CreateTarget(${PROJECT_NAME} EXECUTABLE)

target_link_libraries(${PROJECT_NAME} Macros)
target_link_libraries(${PROJECT_NAME} Networking)