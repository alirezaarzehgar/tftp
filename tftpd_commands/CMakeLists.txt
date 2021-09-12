project(tftpd_commands)

add_library(${PROJECT_NAME}
    src/validator.c
    src/parse_address.c
    src/tftp_sock_init.c
)

add_library(lib::tftpd_commands ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)