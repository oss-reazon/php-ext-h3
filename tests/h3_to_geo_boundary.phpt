--TEST--
h3_to_geo_boundary
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
var_dump(h3_to_geo_boundary(0x892f5aaca4bffff));
?>
--EXPECT--
array(6) {
  [0]=>
  array(2) {
    [0]=>
    float(35.646051565034)
    [1]=>
    float(139.71294527806)
  }
  [1]=>
  array(2) {
    [0]=>
    float(35.647804711225)
    [1]=>
    float(139.71237937458)
  }
  [2]=>
  array(2) {
    [0]=>
    float(35.648277006107)
    [1]=>
    float(139.71039614878)
  }
  [3]=>
  array(2) {
    [0]=>
    float(35.646996173664)
    [1]=>
    float(139.70897892295)
  }
  [4]=>
  array(2) {
    [0]=>
    float(35.645243080517)
    [1]=>
    float(139.70954487594)
  }
  [5]=>
  array(2) {
    [0]=>
    float(35.64477076677)
    [1]=>
    float(139.71152800526)
  }
}
