--TEST--
h3_from_string
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_from_string('892f5aaca4bffff'));
?>
--EXPECT--
int(617826212790403071)
