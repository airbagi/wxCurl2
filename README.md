# wxCurl2 - wxWidgets library to connect to Curl

Based on well-known wxCode component wxCurl
Original Author: Francesco Montorsi

# What was done

I added this source because this library never was supported. I couldn't find any of authors and supporters, I've created this branch.
I fixed several bugs (concerning http behaviour) and moved to https (secure HTTP) protocol that was currently unsupported.

# Dependences

In order to compile you will need to compile CURL library.

# How to compile

First of all get source using flag **--recurse-submodules**, to get thirdparty libraries.
You'll need:

1. Curl library
2. Zlib library
3. OpenSSL library (or if you want, you can try to build Curl with Windows Cryptography)
4. Crypto library (now the part of OpenSSL)
5. libssh2 (if you want to compile curl with ssh2 protocol) - optional, not included into submodules

I'm using [TDM GCC](https://jmeubank.github.io/tdm-gcc/) compiler. It successfully compiled [wxWidgets](https://www.wxwidgets.org/) for me without any troubles several years ago, so I became addict to this toolchain.
    
On windows you would like to install [MSYS2](https://www.msys2.org/) in order to make compilation process smoother.
If you don't have path to TDM GCC yet, run MSYS2 command:

`export PATH="/c/TDM-GCC-32/bin:$PATH"`

replacing the sample path wherever you TDM-GCC compiler has been installed into.

## Compiling OpenSSL

First of all, checkout the branch, that can be easily compiled.
If you checkout the last one "alpha" branch, you can have difficulties.
For example, I've used **OpenSSL_1_1_1k**

```bash
git fetch
git checkout OpenSSL_1_1_1
```

TDM-GCC uses mingw make tools, so run commands:

```bash
cd openssl
./Configure no-shared --prefix=$PWD/dist mingw
mingw32-make depend
mingw32-make
```

**no-shared** is used to create a static library. Alternatively, the **-static** parameter can be used.

You have to correct Makefile line:
```bash
CFLAGS=-Wall -O3 -fomit-frame-pointer -DWINVER=0x0501 -D_WIN32_WINNT=0x0501
```

if you have errors like this one:

```
undefined reference to `getnameinfo'
```

Compile may go wrong if you have Windows SDK on the path.

If there's error `multiple declaration of wspiapi` you have to remark one line in `e_os.h`:

```cpp
// #     include <wspiapi.h>
```

The last successfull build with mingw32 was in openssl-1.0.2a. So if you don't want to mess with all this stuff, checkout that branch or download sources. They will compile with less effort.

## Compiling ZLib

```bash
cd ..
cd zlib
./configure
mingw32-make.exe -f ./win32/Makefile.gcc
```

## Compiling Curl library

There are several options how to compile Curl library on Windows.
In order to use SSL/TLS in your projects, you have to compile it with **-ssl** option.
Also I recommend to compile it with **-zlib** option.
And, optionally, you can use **-ssh2** option.

```bash
cd ..
cd curl/lib
mingw32-make -f Makefile.m32 CFG=-ssl-sspi-zlib ZLIB_PATH=../../zlib OPENSSL_PATH=../../openssl
```

If you get compilation errors you can modify Makefile.m32:

```
CFLAGS = $(CURL_CFLAG_EXTRAS) -g -O2 -Wall -W -DCURL_WINDOWS_APP
```

This may help to build library on Windows.

## Compiling wxCurl2

There two ways to compile **wxCurl2** library: using makefile, and using [CodeBlocks](https://www.codeblocks.org) project file.
You need to have compiled wxWigets library and $(WXWIN) environment variable set to its path.

The other way to compile using makefile:
```bash
cd build
mingw32-make SHELL=CMD.exe -f makefile.gcc WX_DEBUG=0 DEBUG_FLAG=0 BUILD=release WX_SHARED=0 WX_UNICODE=1 UNICODE=1 WX_VERSION=31 WX_MONOLITHIC=1 SHARED=0 CXXFLAGS="-std=gnu++11" 
``` 

If you need debug version:
```bash
cd build
mingw32-make SHELL=CMD.exe -f makefile.gcc WX_DEBUG=1 DEBUG_FLAG=1 BUILD=debug WX_SHARED=0 WX_UNICODE=1 UNICODE=1 WX_VERSION=31 WX_MONOLITHIC=1 SHARED=0 CXXFLAGS="-std=gnu++11" 
``` 
