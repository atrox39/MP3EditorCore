CXX=g++
FILES=src/main.cpp src/mp3.cpp
OUTPUT=docs/mp3tags
CXXFLAGS=-std=c++17 -Wall -Wextra -O2

build:
	$(CXX) $(CXXFLAGS) $(FILES) -o $(OUTPUT)
build_em:
	emcc $(CXXFLAGS) src/mp3.cpp -o $(OUTPUT).js -s WASM=1 -s EXPORTED_FUNCTIONS="['_malloc','_free','_ReadMP3_EM']" -s EXPORTED_RUNTIME_METHODS="['HEAPU8','ccall', 'cwrap']" -lembind -s ASSERTIONS=1