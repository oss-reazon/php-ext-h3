--TEST--
h3 constants
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php

$constants = [
    'H3_MAX_RESOLUTION' => ['integer', 15],
    'H3_UNIT_KM' => ['integer', 2],
    'H3_UNIT_KM2' => ['integer', 102],
    'H3_UNIT_M' => ['integer', 1],
    'H3_UNIT_M2' => ['integer', 101],
    'H3_VERSION' => ['string', null],
    'H3_VERSION_MAJOR' => ['integer', null],
    'H3_VERSION_MINOR' => ['integer', null],
    'H3_VERSION_PATCH' => ['integer', null],
];

foreach ($constants as $name => [$type, $value]) {
    if (!defined($name)) {
        echo "$name: (undefined)\n";
        continue;
    }

    $cst = constant($name);

    if ($value !== null) {
        if ($cst === $value) {
            echo "$name: OK\n";
        } else {
            echo "$name expect: ";
            var_dump($value);
            echo "$name actual: ";
            var_dump(constant($value));
        }

        continue;
    }

    $actual = gettype($cst);

    if ($actual === $type) {
        echo "$name: OK\n";
        continue;
    }

    echo "$name expect: ($type)\n";
    echo "$name actual: ";
    var_dump($cst);
}

$version = H3_VERSION_MAJOR . '.' . H3_VERSION_MINOR . '.' . H3_VERSION_PATCH;

if (H3_VERSION === $version) {
    echo "H3_VERSION: matched\n";
} else {
    echo "H3_VERSION: mismatched\n";
    var_dump(
        H3_VERSION,
        H3_VERSION_MAJOR,
        H3_VERSION_MINOR,
        H3_VERSION_PATCH
    );
}

?>
--EXPECT--
H3_MAX_RESOLUTION: OK
H3_UNIT_KM: OK
H3_UNIT_KM2: OK
H3_UNIT_M: OK
H3_UNIT_M2: OK
H3_VERSION: OK
H3_VERSION_MAJOR: OK
H3_VERSION_MINOR: OK
H3_VERSION_PATCH: OK
H3_VERSION: matched
