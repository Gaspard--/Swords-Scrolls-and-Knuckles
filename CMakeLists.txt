cmake_minimum_required(VERSION 2.6)

message("
   ▄████████  ▄█     █▄   ▄██████▄     ▄████████ ████████▄     ▄████████
  ███    ███ ███     ███ ███    ███   ███    ███ ███   ▀███   ███    ███
  ███    █▀  ███     ███ ███    ███   ███    ███ ███    ███   ███    █▀
  ███        ███     ███ ███    ███  ▄███▄▄▄▄██▀ ███    ███   ███
▀███████████ ███     ███ ███    ███ ▀▀███▀▀▀▀▀   ███    ███ ▀███████████
         ███ ███     ███ ███    ███ ▀███████████ ███    ███          ███
   ▄█    ███ ███ ▄█▄ ███ ███    ███   ███    ███ ███   ▄███    ▄█    ███
 ▄████████▀   ▀███▀███▀   ▀██████▀    ███    ███ ████████▀   ▄████████▀
                                      ███    ███
   ▄████████  ▄████████    ▄████████  ▄██████▄   ▄█        ▄█          ▄████████
  ███    ███ ███    ███   ███    ███ ███    ███ ███       ███         ███    ███
  ███    █▀  ███    █▀    ███    ███ ███    ███ ███       ███         ███    █▀
  ███        ███         ▄███▄▄▄▄██▀ ███    ███ ███       ███         ███
▀███████████ ███        ▀▀███▀▀▀▀▀   ███    ███ ███       ███       ▀███████████
         ███ ███    █▄  ▀███████████ ███    ███ ███       ███                ███
   ▄█    ███ ███    ███   ███    ███ ███    ███ ███▌    ▄ ███▌    ▄    ▄█    ███
 ▄████████▀  ████████▀    ███    ███  ▀██████▀  █████▄▄██ █████▄▄██  ▄████████▀
                          ███    ███            ▀         ▀
   ▄█   ▄█▄ ███▄▄▄▄   ███    █▄   ▄████████    ▄█   ▄█▄  ▄█          ▄████████    ▄████████
  ███ ▄███▀ ███▀▀▀██▄ ███    ███ ███    ███   ███ ▄███▀ ███         ███    ███   ███    ███
  ███▐██▀   ███   ███ ███    ███ ███    █▀    ███▐██▀   ███         ███    █▀    ███    █▀
 ▄█████▀    ███   ███ ███    ███ ███         ▄█████▀    ███        ▄███▄▄▄       ███
▀▀█████▄    ███   ███ ███    ███ ███        ▀▀█████▄    ███       ▀▀███▀▀▀     ▀███████████
  ███▐██▄   ███   ███ ███    ███ ███    █▄    ███▐██▄   ███         ███    █▄           ███
  ███ ▀███▄ ███   ███ ███    ███ ███    ███   ███ ▀███▄ ███▌    ▄   ███    ███    ▄█    ███
  ███   ▀█▀  ▀█   █▀  ████████▀  ████████▀    ███   ▀█▀ █████▄▄██   ██████████  ▄████████▀
  ▀                                           ▀         ▀
")

project(ssk)

set(HEADER_DIRECTORY "include")
set(SOURCE_DIRECTORY "source")

if (WIN32)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
  if ("$ENV{OGRE_HOME}" STREQUAL "")
    message(FATAL_ERROR "The OGRE_HOME environment variable is not set.")
  endif("$ENV{OGRE_HOME}" STREQUAL "")
  if ("$ENV{OPENALDIR}" STREQUAL "")
    message(FATAL_ERROR "The OPENALDIR environment variable is not set.")
  endif("$ENV{OPENALDIR}" STREQUAL "")
  set(OGRE_HOME $ENV{OGRE_HOME})
  set(OPENALDIR $ENV{OPENALDIR})
else()
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wfloat-conversion -g -O3")
endif(WIN32)

file(GLOB_RECURSE SOURCES_FILE "${SOURCE_DIRECTORY}/*.cpp")
file(GLOB_RECURSE HEADERS_FILE "${HEADER_DIRECTORY}/*.hpp")

find_package(Threads REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(OpenAL REQUIRED)
find_package(PythonLibs REQUIRED)

if (UNIX AND OGRE_RenderSystem_GL_FOUND)
  if (OGRE_PLUGIN_DIR)
    message("-- Found RenderSystem at '${OGRE_PLUGIN_DIR}'")
    file(WRITE resources/cfg/plugins.cfg "PluginFolder=${OGRE_PLUGIN_DIR}\nPlugin=RenderSystem_GL\n")
  elseif (OGRE_PLUGIN_DIR_REL)
    message("-- Found RenderSystem at '${OGRE_PLUGIN_DIR_REL}'")
    file(WRITE resources/cfg/plugins.cfg "PluginFolder=${OGRE_PLUGIN_DIR_REL}\nPlugin=RenderSystem_GL\n")
  else()
    message(FATAL_ERROR "Could not find ogre plugin directory")
  endif()
elseif(WIN32)
  message("-- Found RenderSystem at '${OGRE_HOME}'")
  set(OGRE_PLUGIN ${OGRE_HOME}\\bin\\release\\)
  file(WRITE resources/cfg/plugins.cfg "PluginFolder=${OGRE_PLUGIN}\nPlugin=RenderSystem_GL.dll\n")
else()
  message(FATAL_ERROR "Could not find RenderSystem :(")
endif()

include_directories(
	${HEADER_DIRECTORY}
	SYSTEM ${OGRE_INCLUDE_DIRS}
	SYSTEM ${OIS_INCLUDE_DIR}
	SYSTEM ${OPENAL_INCLUDE_DIR}
	SYSTEM ${PYTHON_INCLUDE_DIR}
)

add_executable(
	${PROJECT_NAME}
	${SOURCES_FILE}
	${HEADERS_FILE}
)

target_link_libraries(
	${PROJECT_NAME}
	${OGRE_LIBRARIES}
        ${OGRE_Overlay_LIBRARIES}
	${OIS_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
        ${OPENAL_LIBRARY}
	${PYTHON_LIBRARY}
)

if (UNIX)
  target_link_libraries(
	${PROJECT_NAME}
        alut
        vorbisfile
        ogg
	dl
	util
  )
elseif (WIN32)
  set(VORBIS_LIB "optimized;C:/OpenAL/libs/libvorbis_static.lib;debug;C:/OpenAL/libs/libvorbis_static.lib")
  set(VORBISFILE_LIB "optimized;C:/OpenAL/libs/libvorbisfile_static.lib;debug;C:/OpenAL/libs/libvorbisfile_static.lib")
  set(ALUT_LIB "optimized;C:/OpenAL/libs/alut.lib;debug;C:/OpenAL/libs/alut.lib")
  set(OGG_LIB "optimized;C:/OpenAL/libs/libogg.lib;debug;C:/OpenAL/libs/libogg.lib")
  target_link_libraries(
	${PROJECT_NAME}
	${VORBIS_LIB}
	${VORBISFILE_LIB}
	${ALUT_LIB}
	${OGG_LIB}
  )
endif(UNIX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
