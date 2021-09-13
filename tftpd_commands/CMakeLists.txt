project(tftpd_commands)

add_library(${PROJECT_NAME}
    src/validator.c
    src/tftp_listener.c
    src/parse_address.c
    src/tftp_sock_init.c
    src/tftp_handle_rrq.c
    src/tftp_handle_wrq.c
    src/tftp_handle_nak.c
)

add_library(lib::tftpd_commands ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)