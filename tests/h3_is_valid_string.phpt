--TEST--
h3_is_valid_string
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_is_valid_string('892f5aaca4bffff'));

// invalid
var_dump(h3_is_valid_string(''));
var_dump(h3_is_valid_string('0'));
var_dump(h3_is_valid_string('ffffffffffffffff'));
?>
--EXPECT--
bool(true)
bool(false)
bool(false)
bool(false)
