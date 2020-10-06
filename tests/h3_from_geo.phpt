--TEST--
h3_from_geo
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// valid
var_dump(h3_from_geo(35.6473863, 139.7103676, 9));

// valid
var_dump(h3_from_geo('35.6473863', '139.7103676', 9));

// invalid resolution
var_dump(h3_from_geo('35.6473863', '139.7103676', 16));
?>
--EXPECTF--
int(617826212790403071)
int(617826212790403071)

Warning: h3_from_geo(): Expected parameter 3 (resolution) to be between 0 and 15, 16 given in %s on line %d
NULL
