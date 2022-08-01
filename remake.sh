#!/bin/bash
git clean -xdf
pip3 uninstall nmslib
Y
cd similarity_search/
cmake .
make
cd ../
cd python_bindings/
python3 setup.py install