# HavokScript 2013.2.0 Terminal
A barebones lua terminal for testing Civilization VI's version of HavokScript. All standard libraries are loaded.

## How to use
First copy `HavokScript_FinalRelease.dll` from `Sid Meier's Civilization VI\Base\Binaries\Win64Steam` to the directory that contains `hks.exe`.

Run standalone
```
# ./hks
# > print("hello, world!")
hello, world!
```
or with a file as argument.
```
# ./hks script.lua
```

**Optional**: Add hks to your user Path variable for ease of use.
