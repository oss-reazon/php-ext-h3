--TEST--
h3_get_faces
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php

// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L892

$arr = [
    0x85283473fffffff => 'single face (expected 1)',
    0x821c37fffffffff => 'edge adjacent (expected 1)',
    0x831c06fffffffff => 'edge crossing, distored (expected 2)',
    0x821ce7fffffffff => 'edge crossing, aligned (expected 2)',
    0x84a6001ffffffff => 'class II pentagon (expected 5)',
    0x85a60003fffffff => 'class III pentagon (expected 5)',
];

foreach ($arr as $h3_index => $desc) {
   $faces = h3_get_faces($h3_index);
   sort($faces, SORT_NUMERIC);
   echo $desc, ': ';
   var_dump($faces);
}
?>
--EXPECT--
single face (expected 1): array(1) {
  [0]=>
  int(7)
}
edge adjacent (expected 1): array(1) {
  [0]=>
  int(1)
}
edge crossing, distored (expected 2): array(2) {
  [0]=>
  int(1)
  [1]=>
  int(6)
}
edge crossing, aligned (expected 2): array(2) {
  [0]=>
  int(7)
  [1]=>
  int(11)
}
class II pentagon (expected 5): array(5) {
  [0]=>
  int(5)
  [1]=>
  int(10)
  [2]=>
  int(14)
  [3]=>
  int(15)
  [4]=>
  int(19)
}
class III pentagon (expected 5): array(5) {
  [0]=>
  int(5)
  [1]=>
  int(10)
  [2]=>
  int(14)
  [3]=>
  int(15)
  [4]=>
  int(19)
}
