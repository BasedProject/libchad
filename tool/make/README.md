# [skel](https://github.com/BasedProject/skel)
 
This is meant to be a well isolated `magic` GNU Makefile.

Everything is collected in `object/`, `source/`, and `library/` (we leave this to you to fill in and provide Makefiles for, consider taking a look at other projects for that.)

`tool/` is for testing and anything that you may apply to the repo itself, you can sort away thing you'd rather not look at.

This is meant to be managed under git. We recommend:
```sh
whatever='so-on-etc-you-get-the-point'
git clone --depth=1 https://github.com/BasedProject/skel "$whatever"
cd "$whatever"
git remote remove origin
git update-ref -d HEAD
git commit -m "init skel"
```
this removes all git history and preps it for being set to whatever you need.

It does everything you could possibly need (ideally) in a consistent structure (as is reasonable.)

By default, we'll attempt to compile all .c/++ files in source/ into a single executable object/

We do PCH on all headers within source/ or object/, and distributed dependency generation.

yacc/bison is supported, however I don't have a good test example and therefore you'll probably have to jimmy it.
That was sourced from an existing example Makefile from a real human who does that kind of thing to himself. Be warned.

We collect most (not all) options in the master GNUmakefile.

using `MAKE.filter` we can choose which headers we DO NOT WANT.
This grants fine grain control and lets you replace things with relative transience.
Default assignment is everything disabled by default.

Keep in mind that you are expected to modify both the GNUmakefile and tool/make/ files when you're trying to change anything significant.
This template isn't meant to help you avoid writing GNU Make, but enable structured design.

If you don't want overkill, then you should probably write BSD Make in your `P`o`S`I`X`-coated wet dreams. You have a supercomputer.

## 00-compiler.mk
Optional. Optional. Selects Clang by default, defaulting to GCC otherwise.

## 01-debug.mk
Important. Debugging / Optimization flags for a respective compiler. Attempts to vectorize.

- Provides DEBUG=1 for debugging. When not present, provides -DNDEBUG.
- Provides VECTORIZE=1 for displaying vectorized code, and VECTORIZE_ALL=1 for all vectorization information.
- provides SANITIZE=1 for fsan.
- Routes CC=gcc|clang to select the correct compiler for CXX. NOT currently reversable.

Note that GCC is much better about vectorization - and debugging information in that regard, and is recommended over clang for that need.

## 01-depend.mk
Optional. Creates Makefile dependencies in object. Only useful after first compilation.

## 01-hardened.mk
Optional. Provides Hardening flags for Release builds.

Specifies to use the Mold linker if possible.

## 03-peru.mk
Disabled by default. Pulls in peru files.

## 10-object.mk
Critical. Compiles code into objects.
Provides TARGET recipe, C/C++ files -> .o.

## 11-bison.mk
Optional. Suports bison/yacc.

## 11-gperf.mk
Optional. Attempts to automatically compile gperf files.

## 11-pch.mk
Optional. Creates PCH/GCH for respective compilers.

## 11-lib.mk
Disabled by default, creates lib${TARGET}.(so|a).

## 99-all.mk
all/run recipe.

## 99-clean.mk
clean recipe.
WIPES. REMOVES ${OBJECT.dir}/* AND ${TARGET}, nonrecursively.
