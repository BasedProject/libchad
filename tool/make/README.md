# [skel](https://github.com/BasedProject/skel)

This is meant to be a well isolated `magic` GNU Makefile.

run `make help`

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
