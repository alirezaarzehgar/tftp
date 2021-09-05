cmake_minimum_required(VERSION 3.0)

project(tftp)

include_directories(.)

configure_file(config.h.in ../config.h)

add_executable(tftp
    common/malloc3d.c
    src/argparse.c
    src/tftp.c
    src/main.c
)