cmake_minimum_required(VERSION 3.11)
include(GNUInstallDirs)
include(FetchContent)

project(st_app
  VERSION 0.0.0
  LANGUAGES CXX
  )

###############################################################################
#
# External dependencies managed through fetchcontent
#
###############################################################################

fetchcontent_declare(facilities
  GIT_REPOSITORY https://github.com/fermi-lat/facilities.git
  GIT_TAG standalone
)

fetchcontent_getproperties(facilities)
if(NOT facilities_POPULATED)
  fetchcontent_populate(facilities)
  add_subdirectory(${facilities_SOURCE_DIR} ${facilities_BINARY_DIR})
endif()



fetchcontent_declare(st_stream
  GIT_REPOSITORY https://github.com/fermi-lat/st_stream.git
  GIT_TAG standalone
)

fetchcontent_getproperties(st_stream)
if(NOT st_stream_POPULATED)
  fetchcontent_populate(st_stream)
  add_subdirectory(${st_stream_SOURCE_DIR} ${st_stream_BINARY_DIR})
endif()



fetchcontent_declare(st_graph
  GIT_REPOSITORY https://github.com/fermi-lat/st_graph.git
  GIT_TAG standalone
)

fetchcontent_getproperties(st_graph)
if(NOT st_graph_POPULATED)
  fetchcontent_populate(st_graph)
  add_subdirectory(${st_graph_SOURCE_DIR} ${st_graph_BINARY_DIR})
endif()



fetchcontent_declare(hoops
  GIT_REPOSITORY https://github.com/fermi-lat/hoops.git
  GIT_TAG standalone
)

fetchcontent_getproperties(hoops)
if(NOT hoops_POPULATED)
  fetchcontent_populate(hoops)
  add_subdirectory(${hoops_SOURCE_DIR} ${hoops_BINARY_DIR})
endif()

find_package(Python2 COMPONENTS Development)

###############################################################################


###############################################################################
#
# ST app targets
#
###############################################################################

add_library(st_app STATIC
  src/AppParGroup.cxx
  src/StApp.cxx
  src/StAppFactory.cxx
  src/StAppGui.cxx
  src/ballistic_main.cxx
)

add_library(ST::app ALIAS st_app)

target_include_directories(st_app
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_link_libraries(st_app
  PUBLIC
    ST::hoops
  PRIVATE
    ST::stream
    ST::graph
    ST::facilities
)


set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/st_app)

install(DIRECTORY st_app DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS st_app
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

install(TARGETS st_app
  EXPORT st_appTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

install(EXPORT st_appTargets
  NAMESPACE    ST::
  DESTINATION  ${INSTALL_CONFIGDIR}
  )

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/st_appConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/st_appConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/st_appConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/st_appConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/st_appConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT st_appTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/st_appTargets.cmake
  NAMESPACE ST::
)

#Register package in user's package registry
export(PACKAGE st_app)
