cmake_minimum_required(VERSION 3.8)
project(rust_cpp_interop)

set(CMAKE_CXX_STANDARD 20)

# Locate cargo
find_program(CARGO_EXE cargo REQUIRED
    HINTS ENV CARGO_HOME
    DOC "The Rust package manager (cargo)"
)

# Set variables for our Rust crate and compiled artifacts
set(RUST_CRATE_DIR ${CMAKE_SOURCE_DIR}/math_rust)
set(CARGO_TARGET_DIR ${RUST_CRATE_DIR}/target)

# Add command to build RUST crate with cargo
add_custom_command(
  OUTPUT "${CARGO_TARGET_DIR}/release/libmath_rust.a"
  COMMAND ${CARGO_EXE} build --release
  WORKING_DIRECTORY ${RUST_CRATE_DIR}
  COMMENT "Building Rust library math_rust"
)

# Custom target to add dependencies on.
add_custom_target(rust_math ALL
  DEPENDS "${CARGO_TARGET_DIR}/release/libmath_rust.a"
)

add_executable(rust_cpp_interop main.cpp)

# Add a dependency so the executable waits for the Rust build to complete.
add_dependencies(rust_cpp_interop rust_math)

# Give our dependency access to the Rust headers.
target_include_directories(rust_cpp_interop PRIVATE ${RUST_CRATE_DIR}/include)

# Link the executable to the Rust archive.
target_link_libraries(rust_cpp_interop PRIVATE ${CARGO_TARGET_DIR}/release/libmath_rust.a)