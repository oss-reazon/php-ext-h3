--TEST--
h3_set_to_multi_polygon k_ring
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L735

// 2-ring in order returned by algo
$h3_indexes = h3_k_ring(0x8930062838bffff, 2);
$mp = h3_set_to_multi_polygon($h3_indexes);

echo 'polygon count matches expected: ';
var_dump(count($mp) === 1);

echo 'loop count matches expected: ';
var_dump(count($mp[0]) === 1);

echo 'coord count matches expected: ';
var_dump(count($mp[0][0]) === 6 * (2 * 2 + 1));

// Same k-ring in random order
$h3_indexes = [
    0x89300628393ffff,
    0x89300628383ffff,
    0x89300628397ffff,
    0x89300628067ffff,
    0x89300628387ffff,
    0x893006283bbffff,
    0x89300628313ffff,
    0x893006283cfffff,
    0x89300628303ffff,
    0x89300628317ffff,
    0x8930062839bffff,
    0x8930062838bffff,
    0x8930062806fffff,
    0x8930062838fffff,
    0x893006283d3ffff,
    0x893006283c3ffff,
    0x8930062831bffff,
    0x893006283d7ffff,
    0x893006283c7ffff,
];

$mp = h3_set_to_multi_polygon($h3_indexes);

echo 'polygon count matches expected: ';
var_dump(count($mp) === 1);

echo 'loop count matches expected: ';
var_dump(count($mp[0]) === 1);

echo 'coord count matches expected: ';
var_dump(count($mp[0][0]) === 6 * (2 * 2 + 1));

$h3_indexes = h3_k_ring(0x8930062838bffff, 6);
sort($h3_indexes, SORT_NUMERIC);
$mp = h3_set_to_multi_polygon($h3_indexes);

echo 'loop count matches expected: ';
var_dump(count($mp[0]) === 1);

?>
--EXPECT--
polygon count matches expected: bool(true)
loop count matches expected: bool(true)
coord count matches expected: bool(true)
polygon count matches expected: bool(true)
loop count matches expected: bool(true)
coord count matches expected: bool(true)
loop count matches expected: bool(true)
