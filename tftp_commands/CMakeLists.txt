project(tftp_commands)

add_library(${PROJECT_NAME} 
    src/file.c
    src/malloc3d.c
    src/validator.c
    src/tftp_sock_init.c
    src/tftp_quit.c
    src/tftp_help.c
    src/tftp_helper.c
    src/tftp_mode.c
    src/tftp_connect.c
    src/tftp_status.c
    src/tftp_get.c
    src/tftp_put.c
)

add_library(lib::tftp_commands ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)