--TEST--
h3_set_to_multi_polygon nested_donuts
--SKIPIF--
<?php if (!extension_loaded("h3") || !function_exists('h3_hex_ring')) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L781

echo 'PENDING';
?>
--EXPECT--
