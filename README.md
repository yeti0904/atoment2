# Atoment (2)!
my new programming language, it works.. 
# Compiling
use `make` to create a normal build and `make release` to make a release build<br>
you can add a variable argument to tell the makefile what platform you are targeting:
```sh
make PLATFORM=windows # compiles for 64bit windows
make PLATFORM=win32   # compiles for 32bit windows
# if you dont give a PLATFORM argument it will just compile for your gcc compiler is targeting
```
# Running
./bin/atm path/to/myprogram.atm
