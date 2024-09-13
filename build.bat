@echo off
REM Batch script to build a CMake project

REM Create a build directory if it doesn't exist
if not exist "build" (
    mkdir build
)

REM Navigate to the build directory
cd build

REM Run CMake to generate the build files
cmake ..

REM Compile the project
cmake --build .

REM Check if the build was successful
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo Build succeeded!

REM Navigate back to the root directory
cd ..

REM Run the executable if build was successful
if exist "build\executable.exe" (
    echo Running the executable...
    build\executable.exe
) else (
    echo Executable not found!
)
