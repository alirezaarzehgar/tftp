cmake_minimum_required(VERSION 3.0)

project(main)

configure_file(config.h.in ../tftp/include/config.h)

add_subdirectory(tftp_commands)
add_subdirectory(tftp)
