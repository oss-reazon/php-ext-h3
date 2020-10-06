--TEST--
h3_k_ring pentagon
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L259
$ring = h3_k_ring(0x821c07fffffffff, 1);
sort($ring, SORT_NUMERIC);
var_dump($ring);
?>
--EXPECT--
array(6) {
  [0]=>
  int(585961082523222015)
  [1]=>
  int(585962182034849791)
  [2]=>
  int(585962731790663679)
  [3]=>
  int(585963281546477567)
  [4]=>
  int(585963831302291455)
  [5]=>
  int(585964381058105343)
}
