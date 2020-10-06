--TEST--
h3_get_base_cell
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_get_base_cell(0x892f5aaca4bffff));
?>
--EXPECT--
int(23)
