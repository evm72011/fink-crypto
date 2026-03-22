set(LIB_NAME ${ORDER_BOOK_LIB_NAME})

add_library(${LIB_NAME} src/order_book.cpp)

target_include_directories(${LIB_NAME}
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${LIB_NAME} PUBLIC ${CORE_LIB_NAME} ${MARKET_LIB_NAME})         

if(ENABLE_TESTING)
    add_subdirectory(tests)
endif()