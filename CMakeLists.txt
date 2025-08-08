add_library(
  st_app STATIC
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
  general_util
  PRIVATE
  st_graph
  st_stream
  facilities
)

if(NOT APPLE)
  target_compile_definitions(st_app PRIVATE TRAP_FPE)
endif()

###### EXECUTABLES ######
add_executable(st_app_main src/st_app_main/TestApp1.cxx)
target_link_libraries(st_app_main PRIVATE st_app)

###### TESTS ######
add_executable(test_st_app src/test/test_main.cxx)
target_link_libraries(test_st_app PRIVATE st_app st_graph CppUnit::CppUnit)

###############################################################
# Installation
###############################################################
install(DIRECTORY st_app DESTINATION ${FERMI_INSTALL_INCLUDEDIR})
install(DIRECTORY pfiles/ DESTINATION ${FERMI_INSTALL_PFILESDIR})

install(
  TARGETS st_app st_app_main test_st_app
  EXPORT fermiTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
