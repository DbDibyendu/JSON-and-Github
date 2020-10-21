# Define library. Only source files here!
project(siYaml VERSION 2.0.1 LANGUAGES C CXX)

find_package(Yaml REQUIRED)

list(APPEND SI_MODULES_PUBLIC "SI_YAML")

set(CONFIG_SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parse_json.cpp)

add_definitions(-D__STDC_FORMAT_MACROS)
set_property(DIRECTORY PROPERTY COMPILE_OPTIONS ${EXTRA_CXX_FLAGS})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()


if(YAML_FOUND)

list(APPEND CONFIG_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parse_translational.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parse_config.c)

endif(YAML_FOUND)


# Add Rule to create a Shared object Library
add_library(${PROJECT_NAME} SHARED ${CONFIG_SRC_FILES})

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../alerts/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../connectivity/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../dashboard/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../iiot/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../cloud/include>
    $<INSTALL_INTERFACE:include>)


# Depend on a library that we defined in the top-level file
target_link_libraries(${PROJECT_NAME} PUBLIC -lm -lpthread -lrt -lyaml )

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)


