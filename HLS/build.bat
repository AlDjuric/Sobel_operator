@echo off
set "SOURCE_FILES=main.c"
set "FPGA_OUTPUT_NAME=ver_1"
set "FPGA_FLAGS= --simulator none --quartus-compile --clock 50MHz "

if not "%1"=="" (
  set "TARGET=%1"
) else (
  set "TARGET=emulate"
)

if "%TARGET%" == "emulate" (
  set "CMD=i++ -march=x86-64 -o %TARGET%.exe" 
) else if "%TARGET%" == "fpga" (
  set "CMD=i++ -march=MAX10 %FPGA_FLAGS% -o %FPGA_OUTPUT_NAME%.exe"
)


set "CMD=%CMD:""="%"

echo %CMD% %SOURCE_FILES%
echo:
%CMD% %SOURCE_FILES%



