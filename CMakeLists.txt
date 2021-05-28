cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(Tower_Defense)
add_executable(Tower_Defense main.cpp  ennemi.cpp ennemi.h interface.cpp interface.h chemin.h chemin.cpp tools.h tools.cpp projectile.h projectile.cpp tour.h tour.cpp grille.h grille.cpp)
ImagineUseModules(Tower_Defense Graphics)
