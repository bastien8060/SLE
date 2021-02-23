x86_64-w64-mingw32-g++ main.cpp -o builds/sle_0.0.1_windows.exe
g++ main.cpp -o builds/sle_0.0.1_$(uname -m | tr -d '\n')
