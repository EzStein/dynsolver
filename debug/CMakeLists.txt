cmake_minimum_required(VERSION 3.10)
project(debug)
set(SRC_FILES main.cpp app.cpp)
set(PUBLIC_HEADER_FILES)
set(PRIVATE_HEADER_FILES app.h)
PREPEND(SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src" "${SRC_FILES}")
PREPEND(PUBLIC_HEADER_FILES "include/${PROJECT_NAME}"
  "${PUBLIC_HEADER_FILES}")
PREPEND(PRIVATE_HEADER_FILES "src/include/${PROJECT_NAME}"
  "${PRIVATE_HEADER_FILES}")
add_executable(${PROJECT_NAME} ${EXE_FLAG} "${SRC_FILES}"
  "${PUBLIC_HEADER_FILES}"
  "${PRIVATE_HEADER_FILES}"
  "${GLAD_SRC_FILE}" "${GLAD_INCLUDE_FILE}")
target_include_directories(${PROJECT_NAME} PUBLIC include
  PRIVATE src/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${WX_WIDGETS_TARGETS}
  OpenGL::GL glad compiler parser mygl glfw)
target_compile_definitions(${PROJECT_NAME} PRIVATE
  GL_VERSION_MAJOR=${GL_VERSION_MAJOR})
target_compile_definitions(${PROJECT_NAME} PRIVATE
  GL_VERSION_MINOR=${GL_VERSION_MINOR})
if(${GL_VERSION_MAJOR} GREATER 3 AND ${GL_VERSION_MINOR} GREATER 2)
# Version larger than 4.3
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    GL_ERROR_CALLBACK)
endif()
if(WIN32)
 target_compile_definitions(${PROJECT_NAME} PRIVATE IS_WINDOWS)
endif()
if ( UNIX )
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
endif()
if ( WIN32 )
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4")
endif()
