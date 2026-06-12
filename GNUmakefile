#!/usr/bin/make -f
.SUFFIXES:

TARGET := $(shell basename $$PWD).out

## 05-external.mk

LIBRARY.dir := library

# these will be copied into chad/ ; we expect these to be in ${LIBRARY.dir}/

LIBRARY.orig := dictate/dictate.c \
                dictate/dictate.h \
                qx/qx.h \
                remove_all/remove_all.h \
                sds/sds.c \
                sds/sds.h \
                sds/sdsalloc.h \
                strlist/strlist.h \
                slurp/slurp.h \
                libini/ini_file.c \
                libini/ini_file.h \
                plumblism/plumblism.h \
                plumblism/plumblism.c \
                terry/terry.h \
                kvec/hvec.h \
                kvec/hlist.h \
                XXX/XXX.h \
                dyrect/dyrect.h \
                roman/roman.c \
                roman/roman.h

# these will be copied into chad/experimental

LIBRARY.experimental :=

## make.mk

CFLAGS   := -std=c23 -O2 -pthread
CPPFLAGS := -I. -Ichad -D_XOPEN_SOURCE=500 -D_GNU_SOURCE -fPIC
LDFLAGS  := -lm

SOURCE.dir := chad
OBJECT.dir := object/source
MAKE.dir := tool/make
MAKE.filter := 11-pch.mk

SEARCH.dir := ${SOURCE.dir} ${SOURCE.dir}/random ${SOURCE.dir}/experimental

## 00-compiler.mk

# Externally overridable with CC=.. CXX=..
PREFER_GCC := 1

## 01-debug.mk

DEBUG          ?= 0
SANITIZE       ?= 0
VECTORIZED_ALL ?= 0
VECTORIZED     ?= 0

## 11-lib.mk

NOT_APART_OF_LIBRARY := main.c
LIBTARGET := libchad

## 11-bison.mk

LFLAGS += --debug --trace
YFLAGS += --debug

## 11-gperf.mk

#GPERF := gperf
#GPERF.orig :=

## 11-pch.mk

HEADER.pch.filter :=

###

# Keep source flat. All filenames have optional, assumed prefixes.

-include ${MAKE.dir}/make.mk
