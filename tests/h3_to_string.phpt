--TEST--
h3_to_string
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
var_dump(h3_to_string(0x892f5aaca4bffff));
?>
--EXPECT--
string(15) "892f5aaca4bffff"
