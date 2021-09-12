project(tftpd)

include_directories(include)

add_executable(${PROJECT_NAME}
    src/main.c
)

target_link_libraries(${PROJECT_NAME}
    lib::tftpd_commands
)