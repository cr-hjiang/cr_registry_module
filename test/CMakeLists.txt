#No need to touch this CMakeLists in most cases.
file(GLOB TEST *c *cpp)

foreach(TEST_CASE ${TEST})
  get_filename_component(FILE_NAME ${TEST_CASE} NAME_WE)
  get_filename_component(EXT_NAME ${TEST_CASE} EXT)
  add_executable(${FILE_NAME} ${FILE_NAME}${EXT_NAME})
  if(NOT "${SRC}" STREQUAL "")
    target_link_libraries(${FILE_NAME} ${PROJECT_NAME})
  elseif("${SRC}" STREQUAL "")
    target_link_libraries(${FILE_NAME} ${EXTERNAL_LIBS})
  endif()
endforeach(${TEST_CASE})
