#!/usr/bin/env bash
set -euo pipefail
# Build script for the project
echo "Cleaning..."
make clean || true
echo "Compiling..."
make -j2
echo "Build complete: ./caserma"
