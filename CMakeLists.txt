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
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wno-unused-parameter --std=c++14 -Wno-deprecated-declarations")

file(GLOB_RECURSE SOURCES_FILE "${SOURCE_DIRECTORY}/*.cpp")
file(GLOB_RECURSE HEADERS_FILE "${HEADER_DIRECTORY}/*.hpp")

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

if (OGRE_RenderSystem_GL_FOUND)
  # Change path to Ogre in plugins.cfg:
  message("Found RenderSystem!")
  file(WRITE resources/cfg/plugins.cfg "PluginFolder=${OGRE_PLUGIN_DIR_REL}
Plugin=RenderSystem_GL
")
else()
  message("Could not find RenderSysteam :(")
endif()

include_directories(
	${HEADER_DIRECTORY}
	${OGRE_INCLUDE_DIRS}
	${OIS_INCLUDE_DIR}
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
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
