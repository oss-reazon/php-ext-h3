--TEST--
h3_is_valid
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_is_valid(0x892f5aaca4bffff));

// invalid
var_dump(h3_is_valid(0));
?>
--EXPECT--
bool(true)
bool(false)
