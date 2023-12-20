<<<<<<< HEAD
# Install script for directory: /Users/angela/42/miiiiiiiii_cd
=======
<<<<<<< HEAD
# Install script for directory: /Users/angnguye/projet_42/ghostintheminishell
=======
# Install script for directory: /Users/angnguye/projet_42/MINISHELL
>>>>>>> master
>>>>>>> master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/Users/angela/42/miiiiiiiii_cd/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
=======
<<<<<<< HEAD
file(WRITE "/Users/angnguye/projet_42/ghostintheminishell/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/Users/angnguye/projet_42/MINISHELL/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> master
>>>>>>> master
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
