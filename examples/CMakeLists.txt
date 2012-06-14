add_executable( 
  example1
  example1.cpp
)

include_directories(
   ${ZIHM_INCLUDE_DIR}
   ${SFML_INCLUDE_DIR}
)

target_link_libraries(
  example1
  zihm
  ${SFML_GRAPHICS_LIBRARY}
  ${SFML_WINDOW_LIBRARY}
  ${SFML_SYSTEM_LIBRARY}
)