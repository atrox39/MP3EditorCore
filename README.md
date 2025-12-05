# MP3EditorCore

MP3EditorCore is a lightweight C++ toolkit for inspecting MP3 metadata. It focuses on reading ID3 tags directly from binary data and comes with a WebAssembly build that powers a simple browser UI for quickly checking track information without uploading files to a server.

## Features
- Detects MP3 files by extension and validates embedded ID3 headers.
- Extracts core ID3v1 tag fields (title, artist, album, year, comment, track, genre).
- Reports the raw ID3v2 header when present for easy comparison.
- Ships with an example CLI application and a zero-backend web UI compiled with Emscripten.

## Repository Layout
- `src/` – C++ sources that parse MP3 headers and expose a minimal tag-reading API.
- `docs/` – Static site assets (`index.html`, `mp3tags.js`, and generated WASM/JS bundles) for the in-browser demo.
- `Makefile` – Convenience targets for native and WebAssembly builds.

## Getting Started

### Prerequisites
- **Native build**: a C++17-compatible compiler (e.g., `g++`) and `make`.
- **WebAssembly build**: [Emscripten](https://emscripten.org/) toolchain configured in your environment.

### Build the native demo
```bash
make build
```
This produces the sample executable at `docs/mp3tags`. The current demo binary reads `demo/example.mp3`; adjust `src/main.cpp` or extend `main` to accept paths as needed.

### Build the WebAssembly bundle
```bash
make build_em
```
The target emits `docs/mp3tags.js` and `docs/mp3tags.wasm`, which power the browser UI.

## Running the Demos
- **CLI**: After building, run the generated binary (for example, `docs/mp3tags`) from a terminal. Update the hard-coded path inside `src/main.cpp` before rebuilding to inspect a specific file.
- **Web UI**: Serve the `docs/` directory (e.g., `python -m http.server 8000` from the project root) and open `http://localhost:8000/docs/`. The page loads entirely in the browser; drag any local `.mp3` to view its tag data.

## Contributing
Issues and pull requests are welcome. Feel free to improve tag parsing, add write support, or enhance the web interface.

## License
This project currently has no explicit license. Please open an issue if you need clarification before using it in your own work.
