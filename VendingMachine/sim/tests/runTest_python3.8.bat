@echo off
:: This batch script starts the TestSuiteRunner and executes the specified test suite.
..\..\..\..\TestSuiteRunner.exe -i python3.8.exe "Workspace/VendingMachine/sim/tests/ExampleTests/TestSuite.py"
pause