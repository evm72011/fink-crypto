set(LIB_NAME ${CORE_LIB_NAME})

add_library(${LIB_NAME} INTERFACE)

target_include_directories(${LIB_NAME}
                           INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
