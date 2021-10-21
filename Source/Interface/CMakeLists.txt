project(Interface)

CreateTarget(${PROJECT_NAME} LIBRARY)

target_link_libraries(${PROJECT_NAME} Serialization)