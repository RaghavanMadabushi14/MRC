#!/usr/bin/env bash
# Host-side unit tests + line coverage for MRC firmware. Run from anywhere:
#   bash tests/run_tests.sh
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/tests/build"
mkdir -p "$OUT"

SOURCES=(
    "$ROOT/MRC/MotorControls.cpp"
    "$ROOT/MRC/CommandDecodeExecute.cpp"
    "$ROOT/MRC/Hardware.cpp"
    "$ROOT/MRC/ServoControls.cpp"
    "$ROOT/MRC/BluetoothReadWrite.cpp"
)

clang++ -std=c++17 -Wall -Wno-pragma-once-outside-header \
    -fprofile-instr-generate -fcoverage-mapping \
    -DMOTOR_MIN_PWM=60 \
    -I"$ROOT/tests/fakes" \
    "$ROOT/tests/test_motors.cpp" "${SOURCES[@]}" \
    -o "$OUT/test_motors"

LLVM_PROFILE_FILE="$OUT/test_motors.profraw" "$OUT/test_motors"

xcrun llvm-profdata merge -sparse "$OUT/test_motors.profraw" -o "$OUT/test_motors.profdata"

echo
echo "=== Coverage ==="
xcrun llvm-cov report "$OUT/test_motors" -instr-profile="$OUT/test_motors.profdata" \
    "$ROOT/MRC/MotorControls.cpp" "$ROOT/MRC/CommandDecodeExecute.cpp"

if [[ "${1:-}" == "--show" ]]; then
    xcrun llvm-cov show "$OUT/test_motors" -instr-profile="$OUT/test_motors.profdata" \
        -show-line-counts-or-regions \
        "$ROOT/MRC/MotorControls.cpp" "$ROOT/MRC/CommandDecodeExecute.cpp"
fi
