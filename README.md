# WSL utility for printing path in Windows style
- Also copies the path into clipboard
- Paths starting with `\mnt` are printed as windows paths
    -  e.g. `/mnt/c/Program Files` will be altered to `C:\Program Files`
- Other paths will start with `\\wsl.localhost\` and distro name
    - e.g. in `/etc/apt` will print `\\wsl.localhost\<your distro name>\etc\apt`
    - Distro name is gathered automatically
        - Curently tested on Ubuntu

# Requirements
- `gcc` - compilation

# Installation
1. Change variable `PREFIX` in Makefile to your desired directory
    - default is `usr/local/bin`

2. `sudo make install` - compiles the program and moves the binary to the `PREFIX` directory