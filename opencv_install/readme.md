# Testing the OpenCV install
---
Example program to test the C++ install of OpenCV.

## Installing OpenCV on Windows 10


Two ways to [install OpenCV](https://docs.opencv.org/master/d0/d3d/tutorial_general_install.html): pre-built binaries or compile from sources
### Installing from binary
Note: The pre-built binary is intended for the latest Visual Studio C++ compiler.

* Download & install the latest [release executable](https://github.com/opencv/opencv/releases)
* Set the environment variables to allow CMake to find OpenCV: 
    * For `Path`, add: `<path_to_opencv_install>\build\x64\bin`
    * In user variables, add new variable `OPENCV_DIR = <path_to_opencv_install>\build\x64\<compiler_version>\lib` (folder which contains the `OpenCVConfig.cmake` file.)
* Done!

## Running the code
### Compile
To compile the source files:
* Clone the repo: https://github.com/m-talha/LearnOpenCV.git
* In the project directory: `mkdir build && cd build`
* `cmake ..`
* `cmake --build . --config Release --target OpenCVInstall`
* `cd opencv_install`
* `cmake --install .`

### Execute
Run the generated executable file in the `build/bin` folder.
