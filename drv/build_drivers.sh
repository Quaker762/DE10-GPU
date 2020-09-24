#!/bin/bash

pushd .
cd gl
make -f Makefile.qnx clean
make -f Makefile.qnx
popd
cd r3d
make -f Makefile.qnx clean
make -f Makefile.qnx
cd ..
