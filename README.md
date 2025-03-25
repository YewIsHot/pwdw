# WSL utility for printing path in Windows style
- Works only for directories in Windows (sub directories of `/mnt`)

# Requirements
- `gcc` - compilation

# Installation
1. Change variable `PREFIX` in Makefile to your desired directory
    - default is `usr/local/bin`

2. `sudo make install` - compiles the program and moves the binary to the `PREFIX` directory