#!/bin/sh

SELF="$(readlink -f "$0")"
ROOT="$(dirname "$(dirname "${SELF}")")"
TESTS="-p /usr/local/php-debug/bin/php-debug --show-diff"

if [ "$#" -gt 0 ]; then
    TESTS="$TESTS $@"
fi

(
    cd "$ROOT" && make && NO_INTERACTION=1 TESTS="$TESTS" make test
)
