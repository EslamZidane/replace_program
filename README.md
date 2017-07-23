# Command-Line Text Replacement Utility

## Development Environment
- This application has beed written using a simple text-editor, Notepad++, and compiled using GNU GCC. I used the "make" utility to make compilation a bit easier.
- You can compile the code directly under the Linux environment or using a linux emulator on windows, I used Cygwin.
- To Compile the code you just have to navigate to its directory with your shell screen and type "make", the make script will auto-compile code files in the directory and the output will be a program named "replace".
- You can execute the output file by preceding its name by "./", on both of linux and Cygwin; ex:
./replace.exe -b  -i -f -l Elephant dog -- test1.txt test2.txt

## Setting-up environment on Windows for non-linux user
1. Download [Cygwin](https://www.cygwin.com/setup-x86.exe)
2. Install Cygwin and [add](https://www.maketecheasier.com/install-configure-cygwin-windows/) GCC and make using its package installler
3. Open Cygwin command-promot and have fun with the code

**Note**: You don't need to go through Cygwin installation steps if you are using a Linux-based environment, GCC and make will then be found by default
