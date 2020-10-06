# PHP H3 extension

PHP bindings for [H3](https://github.com/uber/H3).

* [Requirements](#requirements)
* [Installation](#installation)
* [Constants](#constants)
* [Functions](#functions)
* [Development](#development)

## Requirements

- PHP >= v7.4.8 on a 64-bit Linux system.
    - Due to [the bug fixed in v7.4.8](https://bugs.php.net/bug.php?id=79595),
      PHP < v7.4.8 on Alpine Linux produces wrong results without errors or
      warnings.
    - This extension won't work in 32-bit systems because it expects the size
      of `int` to be 64 bits.
- `git` to clone this repository.
- `cmake` (`cmake3`), `gcc`, `libtool`, and `make` to build H3.
- `autoconf` to build this extension.

```bash
# Alpine Linux 3.12
apk add autoconf cmake gcc git libtool make musl-dev

# Debian 10 (buster)
apt-get install autoconf cmake gcc git libtool make

# CentOS 8
dnf install autoconf cmake gcc git libtool make

# CentOS 7
# `cmake3` is provided by EPEL.
# `which` is used in the installation script to detect `cmake3`.
yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
yum install autoconf cmake3 gcc git libtool make which
```

## Installation

```bash
# 適当なディレクトリにこのリポジトリを clone します。
# サブモジュールが含まれているので、 --recursive オプションを利用します。
git clone --recursive https://github.com/oss-reazon/php-ext-h3.git

# clone したディレクトリへ移動します。
cd php-ext-h3

# ビルドスクリプトを実行します。
# 最後に OK と表示されたら OK です。
# # !! FAILED !! と表示されたら失敗しているので、
# コンソールのログをコピーしてご連絡お願いします。
./scripts/clean-build.sh

# モジュールをインストールします。
# 一般的には root 権限が必要であるはずです。
sudo make install

# 拡張モジュールが自動的に読み込まれるよう、 PHP の設定ファイルを更新します。
# PHP のインストール方法によって設定ファイルの位置は異なります。
# 設定ファイルがどこにあるかは `php --ini` コマンドで確認できます。
# 下記は /etc/php.d ディレクトリに拡張モジュール用の設定ファイルがある場合の
# 例です。
sudo sh -c 'echo extension=h3.so > /etc/php.d/h3.ini'

# 下記コマンドを実行し、 `bool(true)` と表示されれば、インストール完了です。
php -r 'var_dump(extension_loaded("h3"));'

# 完了後はディレクトリを削除しても大丈夫です。
cd ..
rm -rf php-ext-h3
```

## Constants

| Available since | Name | Value | Description |
| --------------- | ---- | ----- | ----------- |
| v0.1.0 | `H3_MAX_RESOLUTION` | `15` | The maximum number of resolution |
| v0.1.0 | `H3_UNIT_KM` | `2` | Used with `h3_edge_length()` |
| v0.1.0 | `H3_UNIT_KM2` | `102` | Used with `h3_hex_area()` |
| v0.1.0 | `H3_UNIT_M` | `1` | Used with `h3_edge_length()` |
| v0.1.0 | `H3_UNIT_M2` | `101` | Used with `h3_hex_area()` |
| v0.1.1 | `H3_VERSION` | (string) | The H3 version |
| v0.1.1 | `H3_VERSION_MAJOR` | (int) | The H3 major version |
| v0.1.1 | `H3_VERSION_MINOR` | (int) | The H3 minor version |
| v0.1.1 | `H3_VERSION_PATCH` | (int) | The H3 patch version |

## Functions

| Available since | C   | PHP |
| --------------- | --- | --- |
|        | compact | h3_compact |
|        | degsToRads | h3_degs_to_rads |
| v0.1.0 | h3Distance | [h3_distance(int $from_h3_index, int $to_h3_index)](#function.h3_distance): `int` |
| v0.1.0 | edgeLength | [h3_edge_length(int $resolution, int $unit)](#function.h3_edge_length): `float|null` |
| v0.1.0 | geoToH3 | [h3_from_geo(float $latitude, float $longitude, int $resolution)](#function.h3_from_geo): `int|null` |
|        | experimentalLocalIjToH3 | h3_from_local_ij |
| v0.1.0 | stringToH3 | [h3_from_string(string $h3_string)](#function.h3_from_string): `int` |
| v0.1.0 | h3GetBaseCell | [h3_get_base_cell(int $h3_index)](#function.h3_get_base_cell): `int` |
|        | getDestinationH3IndexFromUnidirectionalEdge | h3_get_destination_index_from_unidirectional_edge |
| v0.1.0 | h3GetFaces | [h3_get_faces(int $h3_index)](#function.h3_get_faces): `int[]` |
|        | getH3IndexesFromUnidirectionalEdge | h3_get_indexes_from_unidirectional_edge |
|        | getOriginH3IndexFromUnidirectionalEdge | h3_get_origin_index_from_unidirectional_edge |
|        | getPentagonIndexes | h3_get_pentagon_indexes |
|        | getRes0Indexes | h3_get_res0_indexes |
| v0.1.0 | h3GetResolution | [h3_get_resolution(int $h3_index)](#function.h3_get_resolution): `int` |
|        | h3GetUnidirectionalEdge | h3_get_unidirectional_edge |
|        | getH3UnidirectionalEdgeBoundary | h3_get_unidirectional_edge_boundary |
|        | getH3UnidirectionalEdgesFromHexagon | h3_get_unidirectional_edges_from_hexagon |
| v0.1.0 | hexArea | [h3_hex_area(int $resolution, int $unit)](#function.h3_hex_area): `float|null` |
|        | hexRing | h3_hex_ring |
|        | h3Line | h3_line |
|        | h3IndexesAreNeighbors | h3_indexes_are_neighbors |
| v0.1.0 | h3IsPentagon | [h3_is_pentagon(int $h3_index)](#function.h3_is_pentagon): `bool` |
| v0.1.0 | h3IsResClassIII | [h3_is_res_class_iii(int $h3_index)](#function.h3_is_res_class_iii): `bool` |
| v0.1.0 | h3IsValid | [h3_is_valid(int $h3_index)](#function.h3_is_valid): `bool` |
| v0.1.0 | | [h3_is_valid_resolution(int $resolution)](#function.h3_is_valid_resolution): `bool` |
| v0.1.0 | | [h3_is_valid_string(string $h3_string)](#function.h3_is_valid_string): `bool` |
|        | h3UnidirectionalEdgeIsValid | h3_is_valid_unidirectional_edge |
| v0.1.0 | kRing | [h3_k_ring(int $h3_index, int $k_distance)](#function.h3_k_ring): `int[]` |
| v0.1.0 | kRingDistances | [h3_k_ring_distances(int $h3_index, int $k_distance)](#function.h3_k_ring_distances): `int[][]` |
|        | numHexagons | h3_num_hexagons |
| v0.1.0 | polyfill | [h3_polyfill([float, float][] $coordinates, [float, float][][]|null $holes, int $resolution, bool $is_geo_json = false)](#function.h3_polyfill): `int[]` |
|        | radsToDegs | h3_rads_to_degs |
| v0.1.0 | h3SetToMultiPolygon | [h3_set_to_multi_polygon(int[] $h3_indexes, bool $as_geo_json = false)](#function.h3_set_to_multi_polygon): `[float, float][][][]` |
|        | h3ToCenterChild | h3_to_center_child |
|        | h3ToChildren | h3_to_children |
| v0.1.0 | h3ToGeo | [h3_to_geo(int $h3_index)](#function.h3_to_geo): `[float, float]` |
| v0.1.0 | h3ToGeoBoundary | [h3_to_geo_boundary(int $h3_index)](#function.h3_to_geo_boundary): `[float, float][]` |
|        | experimentalH3ToLocalIj | h3_to_local_ij |
|        | h3ToParent | h3_to_parent |
| v0.1.0 | h3ToString | [h3_to_string(int $h3_index)](#function.h3_to_string): `string` |
|        | uncompact | h3_uncompact |

### 関数概要

この PHP 拡張において、 H3 インデックスは整数で表現されます。

```php
var_dump(h3_from_geo(35.6473863, 139.7103676, 9));
// int(617826212790403071)

var_dump(h3_from_string('892f5aaca4bffff'));
// int(617826212790403071)

var_dump(h3_to_string(0x892f5aaca4bffff));
// string(15) "892f5aaca4bffff"
```

- `PHP_INT_MAX` を超える数値となることは、 H3 インデックスの仕様上、ありません。
    - ないと思いますが、 32bit 環境だと超えてしまうため、 64bit 環境が必須です。

H3 インデックスを引数として受け取る関数は、それが
H3 インデックスとして正しい値かどうかを検証しません。

正しくない H3 インデックスを渡した場合、適当な値が返却されます。  
多くの場合、 H3 インデックスが `0` であると解釈され、そのまま計算されます。

> [h3-js](https://github.com/uber/h3-js) v3.6.4 の挙動に合わせています。

これを防ぎたい場合は、事前に [`h3_is_valid()`](#function.h3_is_valid) や
[`h3_is_valid_string()`](#function.h3_is_valid_string)
を利用して、引数を検証してから関数へ渡すようにしてください。

* * *

<a name="function.h3_distance"></a>

### h3_distance(int $from_h3_index, int $to_h3_index): `int`

与えられた 2 つの H3 インデックス の距離を取得します。

- 同一の H3 インデックスであれば `0`
- 隣接する H3 インデックスであれば `1`
- 隣接する H3 インデックスの更に隣の H3 インデックスであれば `2`
- 解像度が異なっていたり、離れすぎている場合など、
  ライブラリが距離の計算に失敗した場合は `-1`

```php
$origin = 0x892f5aaca4bffff;

// 同一の H3 インデックスなら 0
var_dump(h3_distance($origin, $origin));
// int(0)

$rings = h3_k_ring_distances($origin, 2);
var_dump(h3_distance($origin, $rings[1][0]));
// int(1)
var_dump(h3_distance($origin, $rings[2][0]));
// int(2)

// 解像度が異なると -1
var_dump(h3_distance(h3_from_geo(37.5, -122, 9), h3_from_geo(37.5, -122, 10)));
// int(-1)

// 距離が離れすぎていると -1
var_dump(h3_distance(h3_from_geo(37.5, -122, 9), h3_from_geo(-37.5, 122, 9)));
// int(-1)
```

* * *

<a name="function.h3_edge_length"></a>

### h3_edge_length(int $resolution, int $unit): `float|null`

与えられた解像度における六角形の一片の長さを、
`$unit` で指定された単位で取得します。

`$unit` には `H3_UNIT_M` もしくは `H3_UNIT_KM` を指定できます。

引数に無効な値が渡された場合は `null` を返却します。

```php
var_dump(h3_edge_length(9, H3_UNIT_M));
// float(174.3756681)

var_dump(h3_edge_length(16, H3_UNIT_M));
// Warning: h3_edge_length(): Expected parameter 1 (resolution) to be between 0 and 15, 16 given in %s on line %d
NULL
```

* * *

<a name="function.h3_from_geo"></a>

### h3_from_geo(float $latitude, float $longitude, int $resolution): `int|null`

与えられた緯度経度から H3 インデックスを取得します。

失敗時は `null` を返却します。

```php
var_dump(h3_from_geo(35.6473863, 139.7103676, 9));
// int(617826212790403071)

// 無効な解像度 $resolution
var_dump(h3_from_geo(35.6473863, 139.7103676, 16));
// Warning: h3_from_geo(): Expected parameter 3 (resolution) to be between 0 and 15, 16 given in %s on line %d
// NULL
```

* * *

<a name="function.h3_from_string"></a>

### h3_from_string(string $h3_string): `int`

与えられた H3 インデックスの文字列表現を数値に変換します。

引数が H3 インデックスとして正しくなくとも、エラーとせずに数値を返却します。  
厳密にチェックするためには、事前に引数を
[`h3_is_valid_string()`](#function.h3_is_valid_string) で検証するか、
返り値を [`h3_is_valid()`](#function.h3_is_valid) で検証してください。

```php
var_dump(h3_from_string('892f5aaca4bffff'));
// int(617826212790403071)

// H3 インデックスとして正しくない文字列の場合でも数値を返却します。
var_dump(h3_from_string('1'));
// int(1)

// この関数は基本的に (int)base_convert(string, 16, 10) と同じ結果になりますが、
// 文字列に 16 進数として不正な文字が入っていた場合の扱いが異なります。
// base_convert() は不正な文字をスキップしますが、
// h3_from_string() は不正な文字が出現すると、そこで変換処理を終了します。

// 'x' は 16 進数として正しい文字ではないので、そこで変換処理が終了します。
var_dump(h3_from_string('1x0'));
// int(1)

// base_convert() は正しくない文字をスキップします。
// この場合は base_convert('10', 16, 10) と同じ結果になります。
var_dump(base_convert('1x0', 16, 10));
// string(2) "16"
```

* * *

<a name="function.h3_get_base_cell"></a>

### h3_get_base_cell(int $h3_index): `int`

与えられた H3 インデックスから Base Cell を取得します。

```
var_dump(h3_get_base_cell(0x892f5aaca4bffffl));
// int(23)
```

* * *

<a name="function.h3_get_faces"></a>

### h3_get_faces(int $h3_index): `int[]`

与えられた H3 インデックスが属する二十面体の面のインデックスを配列として
取得します。

配列の順番は保証されません。

```php
var_dump(h3_get_faces(0x85283473fffffff));
// array(1) {
//   [0]=>
//   int(7)
// }
```

* * *

<a name="function.h3_get_resolution"></a>

### h3_get_resolution(int $h3_index): `int`

与えられた H3 インデックスから解像度を取得します。

```
var_dump(h3_get_resolution(0x892f5aaca4bffff));
// int(9)
```

* * *

<a name="function.h3_hex_area"></a>

### h3_hex_area(int $resolution, int $unit): `float|null`

与えられた解像度の 1 エリアあたりの面積を、
`$unit` で指定された単位で取得します。

`$unit` には `H3_UNIT_M2` もしくは `H3_UNIT_KM2` を指定できます。

引数に無効な値が渡された場合は `null` を返却します。

```php
var_dump(h3_hex_area(9, H3_UNIT_M2));
// float(105332.5)
```

* * *

<a name="function.h3_is_pentagon"></a>

### h3_is_pentagon(int $h3_index): `bool`

与えられた H3 インデックスが示すエリアが五角形かどうかを検証します。

```php
// H3 インデックスが五角形の場合
var_dump(h3_is_pentagon(0x821c07fffffffff));
// bool(true)

// H3 インデックスが六角形の場合
var_dump(h3_is_pentagon(0x892f5aaca4bffff));
// bool(false)
```

* * *

<a name="function.h3_is_res_class_iii"></a>

### h3_is_res_class_iii(int $h3_index): `bool`

与えられた H3 インデックスが Class III であるかどうかを検証します。

```
// H3 インデックスが Class III である場合
var_dump(h3_is_res_class_iii(0x892f5aaca4bffff));
// bool(true)

// H3 インデックスが Class II である場合
var_dump(h3_is_res_class_iii(0x882f5aaca5fffff));
// bool(false)
```

* * *

<a name="function.h3_is_valid"></a>

### h3_is_valid(int $h3_index): `bool`

与えられた H3 インデックスが H3 インデックスとして正しいかどうかを検証します。

```php
var_dump(h3_is_valid(0x892f5aaca4bffff));
// bool(true)

// 無効な H3 インデックス
var_dump(h3_is_valid(0));
// bool(false)
```

* * *

<a name="function.h3_is_valid_resolution"></a>

### h3_is_valid_resolution(int $resolution): `bool`

与えられた解像度が解像度として正しいかどうかを検証します。

解像度は 0 以上 15 以下の整数である必要があります。

```php
var_dump(h3_is_valid_resolution(0));
// bool(true);

var_dump(h3_is_valid_resolution(15));
// bool(true);

var_dump(h3_is_valid_resolution(-1));
// bool(false);

var_dump(h3_is_valid_resolution(16));
// bool(false);
```

* * *

<a name="function.h3_is_valid_string"></a>

### h3_is_valid_string(string $h3_string): `bool`

与えられた文字列が H3 インデックスの文字列表現として正しく、かつ正しい
H3 インデックスかどうかを検証します。

```php
var_dump(h3_is_valid_string('892f5aaca4bffff'));
// bool(true)

var_dump(h3_is_valid_string(''));
// bool(false)

// 文字列表現としては正しいが、正しい H3 インデックスではない。
var_dump(h3_is_valid_string('ffffffffffffffff'));
// bool(false)
```

* * *

<a name="function.h3_k_ring"></a>

### h3_k_ring(int $h3_index, int $k_distance): `int[]`

与えられた H3 インデックスを含む、周辺距離 `$k_distance` 以内の H3 インデックス
を全て取得します。

- `$k_distance` = `0` は自分自身のみを返却します。
- `$k_distance` = `1` は自分自身と、隣接している全てのエリアの
  H3 インデックスを返却します。
    - 典型的には、自分自身が六角形であり、隣接しているエリアは
      6 箇所となるため、計 7 個の H3 インデックスが返却されます。
    - 但し、自分自身が五角形である場合など、より少ない個数になる場合があります。
- `$k_distance` = `2` は自分自身と、隣接している全てのエリア、
  さらにそれらに隣接している全てのエリアの H3 インデックスを返却します。

返却される配列の順序は保証されません。

`h3_k_ring()` は、 [`h3_k_ring_distances()`](#function.h3_k_ring_distances)
を距離ごとの二次元配列にせず、一次元配列にしたものです。

```php
// k_distance = 0 なら自分自身のみ。
var_dump(h3_k_ring(0x892f5aaca4bffff, 0));
// array(1) {
//   [0]=>
//   int(617826212790403071) 
// }

// k_distance = 1 なら、自分自身と、隣接する全てのエリアのインデックス。
// 順序は保証されない。
var_dump(h3_k_ring(0x892f5aaca4bffff, 1));
// array(7) {
//   [0]=>
//   int(617826212790403071)
//   [1]=>
//   int(617826213047042047)
//   ...
//   [6]=>
//   int(617826212791451647)
// }
```

* * *

<a name="function.h3_k_ring_distances"></a>

### h3_k_ring_distances(int $h3_index, int $k_distance): `int[][]`

与えられた H3 インデックスを含む、周辺距離 `$k_distance` 以内の H3 インデックス
を、距離ごとに分けて取得します。

返却される配列の順序は保証されません。

距離ごとに分ける必要がない場合は、 [`h3_k_ring()`](#function.h3_k_ring)
が利用できます。

```php
var_dump(h3_k_ring_distances(0x892f5aaca4bffff, 0));
// array(1) {
//   [0]=>
//   array(1) {
//     [0]=>
//     int(617826212790403071)
//   }
// }

var_dump(h3_k_ring_distances(0x892f5aaca4bffff, 1));
// array(1) {
//   [0]=>
//   array(1) {
//     [0]=>
//     int(617826212790403071)
//   }
//   [1]=>
//   array(6) {
//     [0]=>
//     int(617826212789878783)
//     [1]=>
//     int(617826212790665215)
//     ...
//     [5]=>
//     int(617826213048877055)
//   }
// }
```

* * *

<a name="function.h3_polyfill"></a>

### h3_polyfill([float, float][] $coordinates, [float, float][][]|null $holes, int $resolution, bool $is_geo_json = false): `int[]`

`$coordinates` で表現された多角形のうち、 `$holes` で表現された **穴**
を除いた箇所を埋めるために必要な H3 インデックスを配列として取得します。

- `$coordinates` は緯度経度のペアの配列です。
- `$holes` は緯度経度のペアの配列、の配列です。
- `$resolution` は H3 インデックスの解像度です。
- `$is_geo_json` に `true` を指定すると、緯度経度のペアは
  `[float $latitude, float $longitude]` ではなく
  `[float $longitude, float $latitude]` であると見做されます。
- 返り値の配列の順序は保証されません。

この処理は低速であるため、パフォーマンスにはご注意ください。

> see https://h3geo.org/docs/api/regions polyfill

```php
// H3 インデックスで埋めたい多角形を、各頂点の緯度経度の配列として表現する。
$coordinates = [
    [float $latitude, float $longitude],
    [float $latitude, float $longitude],
    // ...
];

// $coordinates で示された多角形のうち、埋めないでおきたい **穴** も
// 多角形の緯度経度の配列として表現する。
// 穴がない場合は `$holes = null;` で省略可能。
$holes = [
    // 1 つ目の **穴** の各頂点の緯度経度の配列
    [
        [float $latitude, float $longitude],
        [float $latitude, float $longitude],
        // ...
    ],
    // 2 つ目の **穴**
    [
        [float $latitude, float $longitude],
        [float $latitude, float $longitude],
        // ...
    ],
    // ...
];

var_dump(h3_polyfill($coordinates, $holes, 9);
// array(...) {
//   [0]
//   => int(...)
//   [1]
//   => int(...)
//   ...
// }
```

* * *

<a name="function.h3_set_to_multi_polygon"></a>

### h3_set_to_multi_polygon(int[] $h3_indexes, bool $as_geo_json = false): `[float, float][][][]`

与えられた H3 インデックスの配列から、
[GeoJSON の MultiPolygon](https://ja.wikipedia.org/w/index.php?title=GeoJSON&oldid=77130951#%E3%82%B8%E3%82%AA%E3%83%A1%E3%83%88%E3%83%AA%E3%81%AE%E4%BE%8B)
のような緯度経度のペアの配列の配列による Polygon の配列を生成します。

- H3 インデックスは、全ての解像度が等しく、また重複がないことが期待されます。
  解像度がそれぞれ異なっていたり、重複があった場合の動作は未定義です。
- `$as_geo_json` に `true` を指定すると返り値のフォーマットが変わります。
    - 緯度軽度が  `[float $latitude, float $longitude]` ではなく
     `[float $longitude, float $latitude]` となります。
    - 緯度経度のペアの配列の末尾に、先頭と同じ緯度経度のペアが追加されます。
      (**閉じたループ** になります)

返り値のフォーマットは以下の通りです。

```php
[
    // 1 つ目の多角形を表現する緯度経度ペアの配列の配列です。
    [
        // 1 つ目の緯度経度のペアの配列は、多角形の外縁を表現するデータです。
        [
            // $as_geo_json = true だと、
            // [float $longitude, float $latitude]
            // になります。
            [float $latitude_0_0, float $longitude_0_0],
            [float $latitude_0_1, float $longitude_0_1],
            [float $latitude_0_2, float $longitude_0_2],

            // ...

            // $as_gej_json = true だと、配列の末尾に、配列の先頭と同じ
            // 緯度経度のペアが挿入されます。
            // (**閉じたループ** になります)
            //[float $latitude_0_0, float $longitude_0_0],
        ],

        // 2 つ目以降の緯度経度のペアの配列は、
        // 1 つ目で表現された外縁の内側にある **穴** を表現するデータです。

        // 1 つ目の **穴**
        [
            [float $latitude_1_0, float $longitude_1_0],
            [float $latitude_1_1, float $longitude_1_1],
            // ...
        ],

        // 2 つ目の **穴**
        [
            // ...
        ],

        // ...
    ],

    // 2 つ目の多角形
    [
        // ...
    ],

    // ...
];
```

この処理は低速であるため、パフォーマンスにはご注意ください。

```php
var_dump(h3_set_to_multi_polygon([0x89283082837ffff, 0x89283082833ffff]));
// array(2) {
//   [0]=>
//   array(1) {
//     [0]=>
//     array(6) {
//       [0]=>
//       array(2) {
//         [0]=>
//         float(37.775989518838)
//         [1]=>
//         float(-122.42778275313)
//       }
//       [1]=>
//       array(2) {
//         [0]=>
//         float(37.777672214849)
//         [1]=>
//         float(-122.42671162908)
//       }
//       ...
//     }
//   }
//   [1]=>
//   array(1) {
//     [0]=>
//     array(6) {
//       [0]=>
//       array(2) {
//         [0]=>
//         float(37.778206872622)
//         [1]=>
//         float(-122.41971895415)
//       }
//       [1]=>
//       array(2) {
//         [0]=>
//         float(37.776524206993)
//         [1]=>
//         float(-122.42079024542)
//       }
//       ...
//     }
//   }
// }

// $h3_indexes が空である場合、返り値は空の配列になります。
var_dump(h3_set_to_multi_polygon([]));
// array(0) {
// }
```

* * *

<a name="function.h3_to_geo"></a>

### h3_to_geo(int $h3_index): `[float, float]`

与えあれた H3 インデックスの中心点の緯度経度を取得します。

```php
// valid
var_dump(h3_to_geo(0x892f5aaca4bffff));
// array(2) {
//   [0]=>
//   float(35.646523891303)
//   [1]=>
//   float(139.7109620883)
// }
```

* * *

<a name="function.h3_to_geo_boundary"></a>

### h3_to_geo_boundary(int $h3_index): `[float, float][]`

与えられた H3 インデックスから、そのインデックスが示す六角形
(場合によっては五角形) の各頂点の緯度経度のペアを、二次元配列として取得します。

```php
var_dump(h3_to_geo_boundary(0x892f5aaca4bffff));
// array(6) {
//   [0] =>
//   array(2) {
//     [0]=>
//     float(35.646051565034)
//     [1]=>
//     float(139.71294527806)
//   }
//   [1]=>
//   array(2) {
// ...
```

* * *

<a name="function.h3_to_string"></a>

### h3_to_string(int $h3_index): `string`

与えられた H3 インデックス を文字列表現に変換します。  

```php
var_dump(h3_to_string(0x892f5aaca4bffff));
// string(15) "892f5aaca4bffff"
```

<a name="development"></a>

## 開発方法

```bash
# このリポジトリを clone し、 clone したディレクトリへ移動します。

# コードを編集します。
# 編集対象は主に h3.c になります。
# 必要に応じて php_h3.h を編集することもあるかもしれません。

# tests ディレクトリ以下にテストファイルを作成します。

# Alpine Linux 用にクリーンビルド、テストを実行します。
docker-compose run --rm alpine scripts/clean-build.sh debug

# Debian 用にクリーンビルド、テストを実行します。
docker-compose run --rm debian scripts/clean-build.sh debug

# CentOS 7 用にクリーンビルド、テストを実行します。
docker-compose run --rm centos7 scripts/clean-build.sh debug

# 同一の OS に対して何度もビルド、テストを実行する場合は、
# scrits/run-tests.sh を利用します。
docker-compose run --rm centos7 scripts/run-tests.sh

# scripts/run-tests.sh では、特定のファイルだけをテストすることもできます。
docker-compose run --rm cento7 scripts/run-tests.sh tests/h3_to_geo.phpt tests/h3_to_string.phpt

# その他オプションは scripts/run-tests.sh -h で確認してください。
# また、 `docker-compose run --rm` をシェルの alias に登録しておくと便利です。

# OS を切り替えたり、 config.m4 や h3 自体のブランチを変更した後は
# scripts/clean-build.sh debug を実行するようにしてください。
```

PHP 拡張に関するドキュメントはまとまっておらず、解説サイトも非常に少ないため、
PHP のソースコードを読みながら編集することになると思います。

よく参照することになるだろうファイルは以下の通りです。

- [`Zend/zend_API.h`](https://github.com/php/php-src/blob/master/Zend/zend_API.h)
- [`Zend/zend_API.c`](https://github.com/php/php-src/blob/master/Zend/zend_API.c)
    - よく使うマクロ等はここで定義されている場合が多いです。
- [`ext/standard/array.c`](https://github.com/php/php-src/blob/master/ext/standard/array.c)
    - PHP v7 系になって内部実装が大きく変わりましたが、 `array.c` など standard
      ライブラリは最優先で合わせて改修されています (はずです)。
    - 他のライブラリは v5 時代の古い書き方だったりするので、参考にするなら
      standard 系がいいと思います。

比較的よくまとまっているサイト

- [PHP 公式マニュアル](https://www.php.net/manual/ja/internals2.php)
    - PHP v5.3.3 時代の情報なので、信用はできません。
      ただ、全体像はある程度掴める感じになると思います。
- [Writing PHP Extensions | Zend](https://www.zend.com/resources/writing-php-extensions)
    - 比較的新しいバージョンの情報がまとまっているサイトのうち、
      最も公式に近いと思われます。
    - 最新かどうかはソースと見比べてみないと分かりませんが、
      ソースを検索する手掛かりには十分なります。
- [PHP Internals Book](http://www.phpinternalsbook.com/index.html)
    - PHP 開発者が書いている PHP 内部実装全般の情報です。
    - [GitHub](https://github.com/phpinternalsbook/PHP-Internals-Book)
      を見る限り現在もちゃんとメンテナンスされているので、
      信用度は比較的高いと思われます。

### 動的メモリの確保の方法について

`malloc` ファミリーではなく、 PHP が用意している
[`emalloc`](https://www.php.net/manual/ja/internals2.memory.management.php)
ファミリーを利用するようにしてください。

また、 C99 の可変長配列 (VLA) も利用しないようお願いします。

- `emalloc` はメモリの確保に失敗すると、
   **エラーを出力してプロセスを終了します** 。
   - 終了するので、戻り値が `NULL` でないか確認する必要はありません。
   - VLA だと、失敗した場合はエラーも何も出力せずに終了するため、
     原因の特定が困難になります。
- `malloc` に対する `emalloc` 、 `calloc` に対する `ecalloc` 、
  `realloc` に対応する `erealloc` 、 `free` に対する `efree` があります。
    - 引数、返り値は同じです。
    - `safe_emalloc` など独自の関数もあります。
- `emalloc` 系で確保したメモリは必ず `efree` で解放してください。
- PHP のデバッグ版を利用すると (run-tests.sh はデバッグ版を利用しています)、
  `emalloc` 系で確保されたメモリがスクリプト終了時にも残っている場合、
  警告を出力して異常終了します。
    - テストが失敗するようになるので分かりやすいです。
- H3 は
  [malloc 系を差し替えること出来るので](https://github.com/uber/h3/blob/v3.6.4/dev-docs/custom_alloc.md) 、
  [`-DH3_ALLOC_PREFIX` オプション](scripts/clean-build.sh) を利用して
  `emalloc` ファミリーを使うように差し替えています。

### Valgrind を利用したテストについて

`scripts/run-tests.sh -m` で Valgrind を利用したテストできます。

ただし、 Alpine Linux では実数の計算がおかしくなり、正常な結果にならないため、
利用できません。

> https://bugs.php.net/bug.php?id=79595
> おそらくこれと似たような問題かと思います。

Debian 等であればそういったこともなく実行できますが、わざと `efree`
せずにいても検知してくれないので、何か設定が間違っているかもしれません……。

解放済みのポインタに対するアクセスは検知してくれました。
