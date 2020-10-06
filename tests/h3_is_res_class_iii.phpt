--TEST--
h3_is_res_class_iii
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
echo 'Class III: ';
var_dump(h3_is_res_class_iii(0x892f5aaca4bffff));

echo 'Class II: ';
var_dump(h3_is_res_class_iii(0x882f5aaca5fffff));
?>
--EXPECT--
Class III: bool(true)
Class II: bool(false)
