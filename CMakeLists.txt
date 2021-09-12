cmake_minimum_required(VERSION 3.0)

project(main)

configure_file(config.h.in ../tftp_commands/include/tftp_commands/config.h)

add_subdirectory(tftp_commands)
add_subdirectory(tftp)
add_subdirectory(tftpd_commands)
add_subdirectory(tftpd)
