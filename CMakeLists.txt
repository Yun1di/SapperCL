cmake_minimum_required(VERSION 3.16)
project(Sapper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
add_executable(sapper ${SOURCES})

# укажи свой путь к SFML
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS graphics window system REQUIRED)

target_link_libraries(sapper PRIVATE
    sfml-graphics sfml-window sfml-system)

# чтобы exe находил шрифт рядом
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})