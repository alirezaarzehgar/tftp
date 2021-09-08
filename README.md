# TFTP

This project is implementation of TFTP protocol from scratch

# requirements
- cmake (>= 3.0)

# build and install

```
mkdir build
cd build
cmake ..
cmake --build .
```

# usage
```
./tftp/tftp [options]
```

## options
```
tftp
        -a      address of server
        -c      command put|get
        -f      filename for tftp commands
        -p      port
```

## commands

```
put		send file
get		receive file
connect		connect to remote tftp
binary		set mode to octet
ascii		set mode to netascii
help		get help
?		print help information
quit		exit tftp
status		show current status
```