cmake_minimum_required(VERSION 3.25)
project(JuegoDelPirata)

set(CMAKE_CXX_STANDARD 20)

# 🔽 Incluir la librería JSON de nlohmann desde GitHub (RECOMENDADO)
include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)

# 🔽 Hacemos visible la librería para los subdirectorios
set(JSON_BIBLIO nlohmann_json::nlohmann_json CACHE INTERNAL "json lib")

# 🔽 Agregamos los subdirectorios del proyecto
add_subdirectory(core)
add_subdirectory(app_console)
