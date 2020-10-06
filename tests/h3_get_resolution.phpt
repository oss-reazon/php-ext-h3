--TEST--
h3_get_resolution
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_get_resolution(0x892f5aaca4bffff));
?>
--EXPECT--
int(9)
