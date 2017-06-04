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
set(OIS_DIR "${CMAKE_SOURCE_DIR}/cmake/")
# set(OGRE_DIR "${CMAKE_SOURCE_DIR}/cmake/")

if (WIN32)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
  set(OGRE_HOME "C:\\OgreSDK\\")
else()
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wno-unused-parameter --std=c++14 -Wno-deprecated-declarations -Wno-unused-but-set-parameter -g -O3")
endif(WIN32)

find_package (Threads)

file(GLOB_RECURSE SOURCES_FILE "${SOURCE_DIRECTORY}/*.cpp")
file(GLOB_RECURSE HEADERS_FILE "${HEADER_DIRECTORY}/*.hpp")

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(OpenAL REQUIRED)

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
  message("-- Found RenderSystem at '${OGRE_SDK}'")
  file(WRITE resources/cfg/plugins.cfg "PluginFolder=${OGRE_SDK}\nPlugin=RenderSystem_GL\n")
else()
  message(FATAL_ERROR "Could not find RenderSysteam :(")
endif()

include_directories(
	${HEADER_DIRECTORY}
	${OGRE_INCLUDE_DIRS}
	${OIS_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
)

add_executable(
	${PROJECT_NAME}
	${SOURCES_FILE}
	${HEADERS_FILE}
)

target_link_libraries(
	${PROJECT_NAME}
	${OGRE_LIBRARIES}
	${OIS_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
        ${OPENAL_LIBRARY}
        alut
        vorbisfile
        ogg
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
