@echo off

mkdir build

set packages=%~dp0packages\x64-windows-static
set packages=%packages:\=/%
cmake -S . -B build -G "Visual Studio 16 2019" -A x64 -D CMAKE_CONFIGURATION_TYPES:STRING=Debug -D GE_ISET:STRING=X64 -D GE_LINKAGE:STRING=SHARED -D GE_PACKAGES_DIR:STRING="%packages%" -D GE_PLATFORM:STRING=WINDOWS -D GE_BUILD_SAMPLES:BOOL=TRUE -D GE_BUILD_TEST:BOOL=TRUE 

echo.
set /p input=Open in IDE? (empty for No): 
if not "%input%" == "" (
    cmake --open build
)