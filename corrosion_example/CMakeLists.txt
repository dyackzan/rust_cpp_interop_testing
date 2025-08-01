cmake_minimum_required(VERSION 3.16)
project(corrosion_example LANGUAGES C CXX)

find_package(Eigen3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
        Corrosion
        GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
        GIT_TAG v0.5)
FetchContent_MakeAvailable(Corrosion)

# --- Import Rust crate as CMake target ---
corrosion_import_crate(MANIFEST_PATH ${CMAKE_SOURCE_DIR}/rust_obj_lib/Cargo.toml)

# --- C++ executable ---
add_executable(main_exec main.cpp)
target_link_libraries(main_exec PRIVATE rust_obj_lib)