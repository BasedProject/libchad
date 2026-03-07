#!/usr/bin/make -f
.SUFFIXES:

TARGET := $(shell basename $$PWD).out

## make.mk

CFLAGS   := -std=c23 -O2 -pthread
CPPFLAGS := -I. -Ichad -D_XOPEN_SOURCE=500 -D_GNU_SOURCE -fPIC
LDFLAGS  := -lm

SOURCE.dir := chad
OBJECT.dir := object/source
LIBRARY.dir := library
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
