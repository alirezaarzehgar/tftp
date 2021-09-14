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

## tftp commands

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

## tftpd

### options
- chroot jail support
- daemonized

### Limits
- 32MG upload and download limit

## Setup server

1 - create new user for TFTP Server

```
# useradd -r -M -s /sbin/nologin tftpd
```

2 - create a jail

```
# mkdir /srv/tftp
```

3 - change jail owner

```
# chown tftpd:tftpd /srv/tftp
```

4 - run server

```
# tftpd -l -u tftpd -s /srv/tftp -a 0.0.0.0
```

Then you can test this system simply with tftp command.