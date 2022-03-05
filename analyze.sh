#!/usr/bin/env bash

OUTFILE=__demo

infer run -- gcc `python3-config --cflags` -o $OUTFILE `python3-config --ldflags` -lpython3.9  $1

rm -f $OUTFILE

