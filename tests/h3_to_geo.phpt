--TEST--
h3_to_geo
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
var_dump(h3_to_geo(0x892f5aaca4bffff));
?>
--EXPECT--
array(2) {
  [0]=>
  float(35.646523891303)
  [1]=>
  float(139.7109620883)
}
