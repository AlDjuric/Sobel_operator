@echo off

set "SOURCE_FILES=main.c sobel_filter.c result_buffer.c sample_buffer.c "
set "FPGA_OUTPUT_NAME=ver_1"
set "FPGA_FLAGS_ready= --quartus-compile --clock 50MHz --simulator none"
set "FPAG_FLAGS_sim= --quartus-compile --clock 50MHz "

if not "%1"=="" (
  set "TARGET=%1"
) else (
  set "TARGET=emulate"
)

if "%TARGET%" == "emulate" (
  set "CMD=i++ -march=x86-64 -o %TARGET%.exe" 
) else if "%TARGET%" == "fpga_ready" (
  set "CMD=i++ -march=MAX10 %FPGA_FLAGS_ready% -o %FPGA_OUTPUT_NAME%.exe"
) else if "%TARGET%" == "fpga_test" (
  set "CMD=i++ -march=MAX10 %FPGA_FLAGS% -o %FPGA_OUTPUT_NAME%.exe"
)



set "CMD=%CMD:""="%"

echo %CMD% %SOURCE_FILES%
echo:
%CMD% %SOURCE_FILES%



