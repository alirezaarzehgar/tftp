project(modernize)

add_library(${PROJECT_NAME}
    src/main.c
)

add_library(lib::modernize ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)