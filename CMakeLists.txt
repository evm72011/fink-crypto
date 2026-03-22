cmake_minimum_required(VERSION 3.22)

project(
    fink_crypto
    VERSION 1.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CORE_LIB_NAME "fink-crypto-core")
set(MARKET_LIB_NAME "fink-crypto-market")
set(ORDER_BOOK_LIB_NAME "fink-crypto-orderbook")

option(ENABLE_TESTING "Enable testing." ON)

if(ENABLE_TESTING)
    find_package(GTest REQUIRED)
    include(CTest)
    enable_testing()
endif()

add_subdirectory(libs)
add_subdirectory(apps)