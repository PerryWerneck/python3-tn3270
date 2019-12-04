@echo off 
del /s /q build
python setup.py build 

set PYTHONPATH=.\build\lib.win-amd64-3.7
python testprograms\sample.py
