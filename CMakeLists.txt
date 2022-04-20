add_library(
  st_app SHARED
  src/AppParGroup.cxx
  src/ballistic_main.cxx
  src/StApp.cxx
  src/StAppFactory.cxx
  src/StAppGui.cxx
)
target_include_directories(
  st_app PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>
)

target_link_libraries(
  st_app PUBLIC
  hoops
  PRIVATE
  st_graph
  st_stream
  facilities
  PkgConfig::f2c
)

# target_compile_definitions(st_facilities PUBLIC TRAP_FPE)

# add_executable(test_st_app src/test/test.cxx)
# target_link_libraries(test_st_app PRIVATE st_app PkgConfig::cppunit)

###############################################################
# Installation
###############################################################
install(DIRECTORY st_app DESTINATION ${FERMI_INSTALL_INCLUDEDIR})
install(DIRECTORY pfiles/ DESTINATION ${FERMI_INSTALL_PFILESDIR})

install(
  TARGETS st_app
  # EXPORT fermiTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
