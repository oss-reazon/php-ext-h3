--TEST--
h3_edge_length
--SKIPIF--
<?php if (!extension_loaded("h3")) print "skip"; ?>
--FILE--
<?php
$units = [
    'H3_UNIT_M' => H3_UNIT_M,
    'H3_UNIT_KM' => H3_UNIT_KM,
];

foreach ($units as $name => $unit) {
    foreach (range(0, H3_MAX_RESOLUTION) as $resolution) {
        echo "$name:$resolution: ";
        var_dump(h3_edge_length($resolution, $unit));
    }
}
?>
--EXPECT--
H3_UNIT_M:0: float(1107712.591)
H3_UNIT_M:1: float(418676.0055)
H3_UNIT_M:2: float(158244.6558)
H3_UNIT_M:3: float(59810.85794)
H3_UNIT_M:4: float(22606.3794)
H3_UNIT_M:5: float(8544.408276)
H3_UNIT_M:6: float(3229.482772)
H3_UNIT_M:7: float(1220.629759)
H3_UNIT_M:8: float(461.3546837)
H3_UNIT_M:9: float(174.3756681)
H3_UNIT_M:10: float(65.90780749)
H3_UNIT_M:11: float(24.9105614)
H3_UNIT_M:12: float(9.415526211)
H3_UNIT_M:13: float(3.559893033)
H3_UNIT_M:14: float(1.348574562)
H3_UNIT_M:15: float(0.509713273)
H3_UNIT_KM:0: float(1107.712591)
H3_UNIT_KM:1: float(418.6760055)
H3_UNIT_KM:2: float(158.2446558)
H3_UNIT_KM:3: float(59.81085794)
H3_UNIT_KM:4: float(22.6063794)
H3_UNIT_KM:5: float(8.544408276)
H3_UNIT_KM:6: float(3.229482772)
H3_UNIT_KM:7: float(1.220629759)
H3_UNIT_KM:8: float(0.461354684)
H3_UNIT_KM:9: float(0.174375668)
H3_UNIT_KM:10: float(0.065907807)
H3_UNIT_KM:11: float(0.024910561)
H3_UNIT_KM:12: float(0.009415526)
H3_UNIT_KM:13: float(0.003559893)
H3_UNIT_KM:14: float(0.001348575)
H3_UNIT_KM:15: float(0.000509713)
