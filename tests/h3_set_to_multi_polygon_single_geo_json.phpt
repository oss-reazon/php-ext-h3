--TEST--
h3_set_to_multi_polygon single_geo_json
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
// borrowed from
// https://github.com/uber/h3-js/blob/v3.6.4/test/h3core.spec.js#L652
var_dump(h3_set_to_multi_polygon([0x89283082837ffff], true));
?>
--EXPECT--
array(1) {
  [0]=>
  array(1) {
    [0]=>
    array(7) {
      [0]=>
      array(2) {
        [0]=>
        float(-122.42778275313)
        [1]=>
        float(37.775989518838)
      }
      [1]=>
      array(2) {
        [0]=>
        float(-122.42671162908)
        [1]=>
        float(37.777672214849)
      }
      [2]=>
      array(2) {
        [0]=>
        float(-122.42797132395)
        [1]=>
        float(37.779176594646)
      }
      [3]=>
      array(2) {
        [0]=>
        float(-122.43030214181)
        [1]=>
        float(37.778998255104)
      }
      [4]=>
      array(2) {
        [0]=>
        float(-122.43137319648)
        [1]=>
        float(37.777315558988)
      }
      [5]=>
      array(2) {
        [0]=>
        float(-122.43011350268)
        [1]=>
        float(37.775811202519)
      }
      [6]=>
      array(2) {
        [0]=>
        float(-122.42778275313)
        [1]=>
        float(37.775989518838)
      }
    }
  }
}
