
cd .

chcp 1252

if "%1"=="" ("C:\PROGRA~1\MATLAB\R2024a\bin\win64\gmake"  DEPRULES=1 -j5  -f TestBlink.mk all) else ("C:\PROGRA~1\MATLAB\R2024a\bin\win64\gmake"  DEPRULES=1 -j5  -f TestBlink.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1