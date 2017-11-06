@echo off
:loop
	__Hyperx_BigInteger_Test.exe
	__Hyperx_BigInteger.exe < __Hyperx_Test.txt > __Test_out_1
	__Hyperx_BigInteger_Test.py < __Hyperx_Test.txt > __Test_out_2
	fc __Test_out_1 __Test_out_2
	if not errorlevel 1 goto loop
pause
goto loop