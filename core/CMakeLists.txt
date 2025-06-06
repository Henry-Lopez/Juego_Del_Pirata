# core/CMakeLists.txt

# Busca automáticamente todos los .cpp y .h dentro de src/ e include/
file(GLOB_RECURSE CORE_HEADERS "include/*.h")
file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")

# Crea la biblioteca estática
add_library(core ${CORE_SOURCES} ${CORE_HEADERS})

# Incluye los headers al compilar desde otros módulos
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
