#!/bin/sh

cmake="$(which cmake3 2>/dev/null)"

if [ "$?" -ne 0 ]; then
    cmake="cmake"
fi

DEBUG=
BUILD_TYPE=Release
phpize=phpize

if [ "$1" = debug ]; then
    DEBUG=1
    BUILD_TYPE=Debug
    phpize=phpize-debug
fi

set -eu

SELF="$(readlink -f "$0")"
ROOT="$(dirname "$(dirname "${SELF}")")"

main() {
    set -eux

    cd "$ROOT"

    # clean first
    "$phpize"
    ./configure --enable-h3
    make clean

    # build h3 lib
    cd h3
    # warning: failed to remove CMakeFiles/: Directory not empty
    ( git clean -Xdf || true )
    git clean -Xdf
    rm -f CPackConfig.cmake CPackSourceConfig.cmake
    "$cmake" . \
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
        -DCMAKE_C_FLAGS=-fPIC \
        -DENABLE_COVERAGE=OFF \
        -DH3_PREFIX=php_h3_lib_ \
        -DH3_ALLOC_PREFIX=php_h3_e
    "$cmake" --build . --target h3 --config $BUILD_TYPE
    cd ..

    # build h3.so
    "$phpize"

    if [ "$DEBUG" ]; then
        ./configure \
            --with-php-config=/usr/local/php-debug/bin/php-config-debug \
            --enable-debug \
            --enable-h3
        make -j "$(nproc)"
        make test \
            NO_INTERACTION=1 \
            TESTS="--show-diff -p /usr/local/php-debug/bin/php-debug"
    else
        ./configure --enable-h3
        make -j "$(nproc)"
        make test NO_INTERACTION=1 TESTS="--show-diff"
    fi
}

set +eu

( main )

exit_code="$?"
set +eux

if [ "$exit_code" -ne 0 ]; then
    echo ""
    echo ""
    echo "====================================================================="
    echo "                            !! FAILED !!"
    echo ""
    echo ""
else
    echo ""
    echo ""
    echo "====================================================================="
    echo "                                 OK"
    echo ""
    echo ""
fi
