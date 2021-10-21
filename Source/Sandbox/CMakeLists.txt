project(Sandbox)

CreateTarget(${PROJECT_NAME} EXECUTABLE)

target_link_libraries(${PROJECT_NAME} Interface)
target_link_libraries(${PROJECT_NAME} Networking)
target_link_libraries(${PROJECT_NAME} Serialization)