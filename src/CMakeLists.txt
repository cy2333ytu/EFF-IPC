project(ipc)
cmake_minimum_required(VERSION 3.22)

aux_source_directory(${LIBIPC_PROJECT_DIR}/src/libipc SRC_FILES)
aux_source_directory(${LIBIPC_PROJECT_DIR}/src/libipc/sync SRC_FILES)
aux_source_directory(${LIBIPC_PROJECT_DIR}/src/libipc/platform SRC_FILES)

file(GLOB HEAD_FILES
  ${LIBIPC_PROJECT_DIR}/include/libipc/*.h
  ${LIBIPC_PROJECT_DIR}/src/libipc/*.h
  ${LIBIPC_PROJECT_DIR}/src/libipc/*.inc
  ${LIBIPC_PROJECT_DIR}/src/libipc/circ/*.h
  ${LIBIPC_PROJECT_DIR}/src/libipc/memory/*.h
  ${LIBIPC_PROJECT_DIR}/src/libipc/platform/*.h
  ${LIBIPC_PROJECT_DIR}/src/libipc/utility/*.h)

if (LIBIPC_BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEAD_FILES})
  target_compile_definitions(${PROJECT_NAME}
    INTERFACE
      LIBIPC_LIBRARY_SHARED_USING__
    PRIVATE
      LIBIPC_LIBRARY_SHARED_BUILDING__)
else()
  add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEAD_FILES})
endif()

# set output directory
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_include_directories(${PROJECT_NAME}
  PUBLIC  
    "$<BUILD_INTERFACE:${LIBIPC_PROJECT_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
  PRIVATE ${LIBIPC_PROJECT_DIR}/src
          $<$<BOOL:UNIX>:${LIBIPC_PROJECT_DIR}/src/libipc/platform/linux>)

target_link_libraries(${PROJECT_NAME} PUBLIC pthread rt)


install(
  TARGETS ${PROJECT_NAME}
  EXPORT cpp-ipc-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(EXPORT cpp-ipc-targets
	FILE cpp-ipc-targets.cmake
	NAMESPACE cpp-ipc::
	DESTINATION share/cpp-ipc
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/cpp-ipc-config.cmake.in"
[[include(CMakeFindDependencyMacro)
include("${CMAKE_CURRENT_LIST_DIR}/cpp-ipc-targets.cmake")
]])
configure_file("${CMAKE_CURRENT_BINARY_DIR}/cpp-ipc-config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cpp-ipc-config.cmake" @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cpp-ipc-config.cmake DESTINATION share/cpp-ipc)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cppIpcConfigVersion.cmake DESTINATION share/cpp-ipc)