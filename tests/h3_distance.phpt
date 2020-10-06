--TEST--
h3_distance
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L1274

$from_h3_index = 0x892834600a7ffff;

// $rings = array_map(
//     fn($distance) => h3_hex_ring($from_h3_index, $distance),
//     range(0, 4)
// );
$rings = [
    [
        0x892834600a7ffff
    ],
    [
        0x892834600b7ffff,
        0x892834600a3ffff,
        0x892834600afffff,
        0x892834601dbffff,
        0x892834601d3ffff,
        0x8928346056bffff
    ],
    [
        0x8928346054fffff,
        0x892834600b3ffff,
        0x892834600bbffff,
        0x892834600abffff,
        0x89283460033ffff,
        0x89283460037ffff,
        0x892834601cbffff,
        0x892834601c3ffff,
        0x892834601d7ffff,
        0x8928346056fffff,
        0x89283460563ffff,
        0x8928346057bffff
    ],
    [
        0x89283460543ffff,
        0x8928346054bffff,
        0x89283460087ffff,
        0x8928346008fffff,
        0x89283460017ffff,
        0x89283460007ffff,
        0x8928346003bffff,
        0x89283460023ffff,
        0x89283460027ffff,
        0x89283460153ffff,
        0x892834601cfffff,
        0x892834601c7ffff,
        0x8928346018bffff,
        0x8928346019bffff,
        0x89283460567ffff,
        0x89283460577ffff,
        0x89283460573ffff,
        0x89283460547ffff
    ],
];

echo "start rings\n";

foreach ($rings as $distance => $to_h3_indexes) {
    foreach ($to_h3_indexes as $to_h3_index) {
        $actual = h3_distance($from_h3_index, $to_h3_index);

        if ($actual === $distance) {
            continue;
        }

        echo "rings[$distance]: h3_distance(0x",
            h3_to_string($from_h3_index),
            ', 0x',
            h3_to_string($to_h3_index),
            ') is expected to return ',
            $distance,
            ', but returned ';
        var_dump($actual);
    }
}

echo "end rings\n";

$origin = 0x892834600a7ffff; // h3_from_geo(37.5, -122, 9);
$origin10 = 0x8a2834600a67fff; // h3_from_geo(37.5, -122, 10);
$edge = 0x1591ea6d6533ffff;
$distant_hex = 0x89b96baa133ffff; // h3_from_geo(-37.5, 122, 9);

echo "start failures\n";

foreach (compact('origin10', 'edge', 'distant_hex') as $name => $to_h3_index) {
    $actual = h3_distance($origin, $to_h3_index);

    if ($actual === -1) {
        continue;
    }

    echo "$name: h3_distance(0x",
        h3_to_string($origin),
        ', 0x',
        base_convert($to_h3_index, 10, 16),
        ') is expected to return -1, but returned ';
    var_dump($actual);
}

echo "end failures\n";
?>
--EXPECT--
start rings
end rings
start failures
end failures
