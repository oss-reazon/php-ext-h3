--TEST--
h3_set_to_multi_polygon empty
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// empty
var_dump(h3_set_to_multi_polygon([]));
?>
--EXPECT--
array(0) {
}
