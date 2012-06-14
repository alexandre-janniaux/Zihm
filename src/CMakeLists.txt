set(SRCDIR ${ROOTDIR}/src)

set( 
    SOURCES
    ${SRCDIR}/Widget.cpp
    ${SRCDIR}/Tick.cpp
    ${SRCDIR}/Button.cpp
    ${SRCDIR}/LineEdit.cpp
    ${SRCDIR}/List.cpp
    ${SRCDIR}/Menu.cpp
    ${SRCDIR}/Slot.cpp
    ${SRCDIR}/Window.cpp
    ${SRCDIR}/Trigger.cpp
    ${SRCDIR}/Drawing.cpp
)

add_library( 
  zihm
  SHARED
  ${SOURCES}
)

target_link_libraries(
  zihm
  ${SFML_GRAPHICS_LIBRARY}
  ${SFML_WINDOW_LIBRARY}
  ${SFML_SYSTEM_LIBRARY}
)

install(
    TARGETS zihm
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
