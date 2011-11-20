#!/bin/bash
QMAKE=`which qmake-qt4 qmake 2> /dev/null | head -n 1`
${QMAKE}
make mocables compiler_rcc_make_all dist
