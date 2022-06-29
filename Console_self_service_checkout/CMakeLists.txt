cmake_minimum_required(VERSION 3.21)
project(kasa_samobslugowa)

set(CMAKE_CXX_STANDARD 14)

add_executable(kasa_samobslugowa main.cpp product.cpp product.h luz.cpp luz.h managment.cpp managment.h employee.cpp employee.h bin.cpp bin.h interface_functions.cpp interface_functions.h)
