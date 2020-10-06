--TEST--
h3_is_pentagon
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
echo 'Hexagon: ';
var_dump(h3_is_pentagon(0x892f5aaca4bffff));

echo 'Pentagon: ';
var_dump(h3_is_pentagon(0x821c07fffffffff));
?>
--EXPECT--
Hexagon: bool(false)
Pentagon: bool(true)
