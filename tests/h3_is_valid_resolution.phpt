--TEST--
h3_is_valid_resolution
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_is_valid_resolution(0));
var_dump(h3_is_valid_resolution(15));

// invalid
var_dump(h3_is_valid_resolution(-1));
var_dump(h3_is_valid_resolution(16));
?>
--EXPECT--
bool(true)
bool(true)
bool(false)
bool(false)
