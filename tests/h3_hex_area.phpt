--TEST--
h3_hex_area
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
$units = [
    'H3_UNIT_M2' => H3_UNIT_M2,
    'H3_UNIT_KM2' => H3_UNIT_KM2,
];

foreach ($units as $name => $unit) {
    foreach (range(0, H3_MAX_RESOLUTION) as $resolution) {
        echo "$name:$resolution: ";
        var_dump(h3_hex_area($resolution, $unit));
    }
}
?>
--EXPECT--
H3_UNIT_M2:0: float(4250550000000)
H3_UNIT_M2:1: float(607221000000)
H3_UNIT_M2:2: float(86745854035)
H3_UNIT_M2:3: float(12392264862)
H3_UNIT_M2:4: float(1770323552)
H3_UNIT_M2:5: float(252903364.5)
H3_UNIT_M2:6: float(36129052.1)
H3_UNIT_M2:7: float(5161293.2)
H3_UNIT_M2:8: float(737327.6)
H3_UNIT_M2:9: float(105332.5)
H3_UNIT_M2:10: float(15047.5)
H3_UNIT_M2:11: float(2149.6)
H3_UNIT_M2:12: float(307.1)
H3_UNIT_M2:13: float(43.9)
H3_UNIT_M2:14: float(6.3)
H3_UNIT_M2:15: float(0.9)
H3_UNIT_KM2:0: float(4250546.848)
H3_UNIT_KM2:1: float(607220.9782)
H3_UNIT_KM2:2: float(86745.85403)
H3_UNIT_KM2:3: float(12392.26486)
H3_UNIT_KM2:4: float(1770.323552)
H3_UNIT_KM2:5: float(252.9033645)
H3_UNIT_KM2:6: float(36.1290521)
H3_UNIT_KM2:7: float(5.1612932)
H3_UNIT_KM2:8: float(0.7373276)
H3_UNIT_KM2:9: float(0.1053325)
H3_UNIT_KM2:10: float(0.0150475)
H3_UNIT_KM2:11: float(0.0021496)
H3_UNIT_KM2:12: float(0.0003071)
H3_UNIT_KM2:13: float(4.39E-5)
H3_UNIT_KM2:14: float(6.3E-6)
H3_UNIT_KM2:15: float(9.0E-7)

