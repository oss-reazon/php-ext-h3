--TEST--
h3_k_ring
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
var_dump(h3_k_ring(0x892f5aaca4bffff, 0));

$ring_1 = h3_k_ring(0x892f5aaca4bffff, 1);
sort($ring_1, SORT_NUMERIC);
var_dump($ring_1);
?>
--EXPECT--
array(1) {
  [0]=>
  int(617826212790403071)
}
array(7) {
  [0]=>
  int(617826212789878783)
  [1]=>
  int(617826212790403071)
  [2]=>
  int(617826212790665215)
  [3]=>
  int(617826212791451647)
  [4]=>
  int(617826213045993471)
  [5]=>
  int(617826213047042047)
  [6]=>
  int(617826213048877055)
}
