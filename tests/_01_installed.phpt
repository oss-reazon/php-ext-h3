--TEST--
h3 installed
--FILE--
<?php

var_dump(extension_loaded('h3'));
$version = phpversion('h3');

if (!is_string($version) || !preg_match('/\A\d+\.\d+\.\d+\z/', $version)) {
    echo 'Unexpected version: ';
    var_dump($version);
}

?>
--EXPECT--
bool(true)
