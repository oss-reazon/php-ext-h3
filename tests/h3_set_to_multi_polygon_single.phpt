--TEST--
h3_set_to_multi_polygon single
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L652
var_dump(h3_set_to_multi_polygon([0x89283082837ffff]));
?>
--EXPECT--
array(1) {
  [0]=>
  array(1) {
    [0]=>
    array(6) {
      [0]=>
      array(2) {
        [0]=>
        float(37.775989518838)
        [1]=>
        float(-122.42778275313)
      }
      [1]=>
      array(2) {
        [0]=>
        float(37.777672214849)
        [1]=>
        float(-122.42671162908)
      }
      [2]=>
      array(2) {
        [0]=>
        float(37.779176594646)
        [1]=>
        float(-122.42797132395)
      }
      [3]=>
      array(2) {
        [0]=>
        float(37.778998255104)
        [1]=>
        float(-122.43030214181)
      }
      [4]=>
      array(2) {
        [0]=>
        float(37.777315558988)
        [1]=>
        float(-122.43137319648)
      }
      [5]=>
      array(2) {
        [0]=>
        float(37.775811202519)
        [1]=>
        float(-122.43011350268)
      }
    }
  }
}
