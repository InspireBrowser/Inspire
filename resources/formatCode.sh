#!/bin/bash

find browser/ remote/ inspirelib/ plugin_*/ -name "*.cpp" -o -name "*.h" | xargs astyle --options=inspire.astyle
