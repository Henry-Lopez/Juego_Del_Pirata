# 🏴‍☠️ Juego del Pirata

Proyecto académico final de Estructuras de Datos. Este sistema permite interpretar pistas y buscar rutas en un mapa basado en grafos. Cuenta con una interfaz en consola estilizada y un **visualizador interactivo en HTML5** para mostrar gráficamente los caminos encontrados con BFS, DFS o Dijkstra.

---

## 📦 Estructura del proyecto

Juego_Del_Pirata/
├── .idea/ # Configuración del IDE CLion
├── app_console/ # Menú principal y lógica de interacción
├── core/ # Lógica de grafos, algoritmos de búsqueda, parser de pistas
├── datos/ # Archivos de entrada (nodos, conexiones, pistas)
├── visualizador/ # Visualizador HTML+JS+Python para mostrar rutas
├── CMakeLists.txt # Configuración para compilar el proyecto
└── README.md # Este archivo

---

## ⚙️ Requisitos

- ✅ [CMake](https://cmake.org/) >= 3.10
- ✅ [g++](https://gcc.gnu.org/) o [clang++](https://clang.llvm.org/)
- ✅ [Python 3](https://www.python.org/) (solo para el visualizador)
- ✅ Navegador moderno (Chrome, Edge, Firefox)
- ✅ CLion (opcional, pero recomendado como IDE principal)

---

## 🧪 Instrucciones para compilar y ejecutar

### 🔧 Compilación en terminal

git clone https://github.com/Henry-Lopez/Juego_Del_Pirata.git
cd Juego_Del_Pirata
mkdir build
cd build
cmake ..
make
./JuegoDelPirata


🖥️ Configuración recomendada en CLion
📍 Paso 1: Entra a Run > Edit Configurations...

📍 Paso 2: En el campo Working directory, pon exactamente:
$PROJECT_DIR$
Esto asegura que el programa lea correctamente los archivos de datos/, sin errores de ruta relativa.

📊 Visualizador Web Interactivo
Opcional, pero útil para visualizar gráficamente las rutas generadas por los algoritmos.

🌐 Instrucciones:
Asegúrate de tener Python 3 instalado.

Abre terminal y navega a la carpeta:
cd visualizador
Inicia un servidor web local:

python -m http.server 8080
Abre tu navegador y visita:

http://localhost:8080
Esto abrirá index.html con el canvas y dibujará la ruta más reciente generada (ej: ruta_dijkstra.json).

🔍 Funcionalidades
Carga de grafo desde archivo (datos/conexiones.txt)

Carga de pistas desde archivo (datos/pistas.txt)

Interpretación textual de pistas (estilo historia)

Algoritmos:

🔵 BFS (Anchura)

🟠 DFS (Profundidad)

🟢 Dijkstra (Ruta más corta)

Exporta la ruta encontrada como .json para usar en el visualizador

Visualización gráfica del recorrido en canvas
