#!/usr/bin/env bash

infer run -- gcc `python3-config --cflags` -o demo `python3-config --ldflags` -lpython3.9  $1

#infer run -- gcc `python3-config --cflags` -o demo `python3-config --ldflags` -lpython3.9  tutorial-8NG.c
