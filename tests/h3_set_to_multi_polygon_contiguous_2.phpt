--TEST--
h3_set_to_multi_polygon contiguous_2
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L674
var_dump(h3_set_to_multi_polygon([0x89283082837ffff, 0x89283082833ffff]));
?>
--EXPECT--
array(1) {
  [0]=>
  array(1) {
    [0]=>
    array(10) {
      [0]=>
      array(2) {
        [0]=>
        float(37.777672214849)
        [1]=>
        float(-122.42671162908)
      }
      [1]=>
      array(2) {
        [0]=>
        float(37.779176594646)
        [1]=>
        float(-122.42797132395)
      }
      [2]=>
      array(2) {
        [0]=>
        float(37.778998255104)
        [1]=>
        float(-122.43030214181)
      }
      [3]=>
      array(2) {
        [0]=>
        float(37.777315558988)
        [1]=>
        float(-122.43137319648)
      }
      [4]=>
      array(2) {
        [0]=>
        float(37.775811202519)
        [1]=>
        float(-122.43011350268)
      }
      [5]=>
      array(2) {
        [0]=>
        float(37.775989518838)
        [1]=>
        float(-122.42778275313)
      }
      [6]=>
      array(2) {
        [0]=>
        float(37.774485085665)
        [1]=>
        float(-122.42652309808)
      }
      [7]=>
      array(2) {
        [0]=>
        float(37.774663325176)
        [1]=>
        float(-122.42419231791)
      }
      [8]=>
      array(2) {
        [0]=>
        float(37.776346021078)
        [1]=>
        float(-122.42312112449)
      }
      [9]=>
      array(2) {
        [0]=>
        float(37.777850477579)
        [1]=>
        float(-122.42438078061)
      }
    }
  }
}
