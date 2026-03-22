set(EXE_NAME fink-crypto-example)
set(EXE_SOURCES "src/main.cpp")

add_executable(${EXE_NAME} ${EXE_SOURCES})

target_link_libraries(${EXE_NAME} PRIVATE ${CORE_LIB_NAME} ${MARKET_LIB_NAME})
