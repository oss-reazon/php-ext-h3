--TEST--
h3_k_ring edge case
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L279
$ring = h3_k_ring(0x8928308324bffff, 1);
sort($ring, SORT_NUMERIC);
var_dump($ring);
?>
--EXPECT--
array(7) {
  [0]=>
  int(617700170129473535)
  [1]=>
  int(617700170129997823)
  [2]=>
  int(617700170130259967)
  [3]=>
  int(617700170131046399)
  [4]=>
  int(617700175888515071)
  [5]=>
  int(617700175889563647)
  [6]=>
  int(617700175891398655)
}
