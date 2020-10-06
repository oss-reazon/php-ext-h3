/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_h3.h"

#define H3_PREFIX php_h3_lib_
#include "h3api.h"

void* php_h3_emalloc(size_t size)
{
	return emalloc(size);
}

void* php_h3_ecalloc(size_t num, size_t size)
{
	return ecalloc(num, size);
}

void* php_h3_erealloc(void* ptr, size_t size)
{
	return erealloc(ptr, size);
}

void php_h3_efree(void* ptr)
{
	efree(ptr);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_distance, 0, 0, 2)
	ZEND_ARG_INFO(0, from_h3_index)
	ZEND_ARG_INFO(0, to_h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_distance)
{
	zend_long from_h3_index, to_h3_index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(from_h3_index)
		Z_PARAM_LONG(to_h3_index)
		// h3-js.h3Distance() returns 0 for invalid arguments
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_LONG(0));

	H3Index from_h = (H3Index)from_h3_index;
	H3Index to_h = (H3Index)to_h3_index;

	int distance = H3_EXPORT(h3Distance)(from_h, to_h);

	RETURN_LONG(distance);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_edge_length, 0, 0, 2)
	ZEND_ARG_INFO(0, resolution)
	ZEND_ARG_INFO(0, unit)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_edge_length)
{
	zend_long resolution;
	zend_long unit;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(resolution)
		Z_PARAM_LONG(unit)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_NULL());

	if (resolution < 0 || resolution > PHP_H3_MAX_RESOLUTION) {
		php_error_docref(
			NULL,
			E_WARNING,
			"Expected parameter 1 (resolution) to be between 0 and %d, "
				"%ld given",
			PHP_H3_MAX_RESOLUTION,
			resolution
		);

		RETURN_NULL();
	}

	if (unit == PHP_H3_UNIT_M) {
		RETURN_DOUBLE(H3_EXPORT(edgeLengthM)(resolution));
	}

	if (unit == PHP_H3_UNIT_KM) {
		RETURN_DOUBLE(H3_EXPORT(edgeLengthKm)(resolution));
	}

	php_error_docref(
		NULL,
		E_WARNING,
		"Expected parameter 2 (unit) to be either H3_UNIT_M (%d) or "
			"H3_UNIT_KM (%d), %ld given",
		PHP_H3_UNIT_M,
		PHP_H3_UNIT_KM,
		unit
	);

	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_from_geo, 0, 0, 3)
	ZEND_ARG_INFO(0, latitude)
	ZEND_ARG_INFO(0, longitude)
	ZEND_ARG_INFO(0, resolution)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_from_geo)
{
	zend_long resolution;
	double latitude, longitude;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_DOUBLE(latitude)
		Z_PARAM_DOUBLE(longitude)
		Z_PARAM_LONG(resolution)
		// h3-js.geoToH3() returns null for invalid arguments.
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_NULL());

	if (resolution < 0 || resolution > PHP_H3_MAX_RESOLUTION) {
		// h3-js.geoToH3() returns null for invalid resolution.
		php_error_docref(
			NULL,
			E_WARNING,
			"Expected parameter 3 (resolution) to be between 0 and %d, "
				"%ld given",
			PHP_H3_MAX_RESOLUTION,
			resolution
		);

		RETURN_NULL();
	}

	GeoCoord location;
	location.lat = H3_EXPORT(degsToRads)(latitude);
	location.lon = H3_EXPORT(degsToRads)(longitude);

	H3Index h = H3_EXPORT(geoToH3)(&location, resolution);

	RETURN_LONG(h);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_from_string, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_string)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_from_string)
{
	zend_string *h3_string;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(h3_string)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_LONG(0));

	H3Index h = H3_EXPORT(stringToH3)(ZSTR_VAL(h3_string));

	RETURN_LONG(h);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_get_base_cell, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_get_base_cell)
{
	zend_long h3_index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(h3_index)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_LONG(0));

	H3Index h = (H3Index)h3_index;

	int base_cell = H3_EXPORT(h3GetBaseCell)(h);

	RETURN_LONG(base_cell);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_get_faces, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_get_faces)
{
	zend_long h3_index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(h3_index)
	ZEND_PARSE_PARAMETERS_END_EX(
		// h3-js.h3GetFaces() returns [1] for an invalid index.
		array_init_size(return_value, 1);
		add_index_long(return_value, 0, 1);
		return
	);

	H3Index h = (H3Index)h3_index;

	int max_face_count = H3_EXPORT(maxFaceCount)(h);
	// OPTIMIZE
	// max_face_count must be either 2 or 5.
	// Using a fixed-length array would get better performance.
	//int *out = (int *)emalloc(max_face_count * sizeof(int));
	int out[5];
	H3_EXPORT(h3GetFaces)(h, out);

	int count = 0;

	for (int i = 0; i < max_face_count; ++i) {
		if (out[i] != -1) {
			++count;
		}
	}

	array_init_size(return_value, count);

	int offset = 0;

	for (int i = 0; i < max_face_count; ++i) {
		if (out[i] != -1) {
			add_index_long(return_value, offset++, out[i]);
		}
	}
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_get_resolution, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_get_resolution)
{
	zend_long h3_index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(h3_index)
		// Somehow h3-js.h3GetResolution() returns NaN for an invalid index.
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_LONG(0));

	H3Index h = (H3Index)h3_index;

	int resolution = H3_EXPORT(h3GetResolution)(h);

	RETURN_LONG(resolution);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_hex_area, 0, 0, 2)
	ZEND_ARG_INFO(0, resolution)
	ZEND_ARG_INFO(0, unit)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_hex_area)
{
	zend_long resolution;
	zend_long unit;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(resolution)
		Z_PARAM_LONG(unit)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_NULL());

	if (resolution < 0 || resolution > PHP_H3_MAX_RESOLUTION) {
		php_error_docref(
			NULL,
			E_WARNING,
			"Expected parameter 1 (resolution) to be between 0 and %d, "
				"%ld given",
			PHP_H3_MAX_RESOLUTION,
			resolution
		);

		RETURN_NULL();
	}

	if (unit == PHP_H3_UNIT_M2) {
		RETURN_DOUBLE(H3_EXPORT(hexAreaM2)(resolution));
	}

	if (unit == PHP_H3_UNIT_KM2) {
		RETURN_DOUBLE(H3_EXPORT(hexAreaKm2)(resolution));
	}

	php_error_docref(
		NULL,
		E_WARNING,
		"Expected parameter 2 (unit) to be either H3_UNIT_M2 (%d) or "
			"H3_UNIT_KM2 (%d), %ld given",
		PHP_H3_UNIT_M2,
		PHP_H3_UNIT_KM2,
		unit
	);

	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_is_pentagon, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_is_pentagon)
{
	zend_long h3_index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(h3_index)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	H3Index h = (H3Index)h3_index;

	if (!H3_EXPORT(h3IsPentagon)(h)) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_is_res_class_iii, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_is_res_class_iii)
{
	zend_long h3_index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(h3_index)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	H3Index h = (H3Index)h3_index;

	if (!H3_EXPORT(h3IsResClassIII)(h)) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_is_valid, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_is_valid)
{
	zend_long h3_index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(h3_index)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	H3Index h = (H3Index)h3_index;

	if (!H3_EXPORT(h3IsValid)(h)) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_is_valid_resolution, 0, 0, 1)
	ZEND_ARG_INFO(0, resolution)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_is_valid_resolution)
{
	zend_long resolution;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(resolution)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	if (resolution < 0 || resolution > PHP_H3_MAX_RESOLUTION) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_is_valid_string, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_string)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_is_valid_string)
{
	zend_string *h3_string;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(h3_string)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	H3Index h = H3_EXPORT(stringToH3)(ZSTR_VAL(h3_string));

	if (!H3_EXPORT(h3IsValid)(h)) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_k_ring, 0, 0, 2)
	ZEND_ARG_INFO(0, h3_index)
	ZEND_ARG_INFO(0, k_distance)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_k_ring)
{
	zend_long h3_index = PHP_H3_INVALID_INDEX;
	zend_long k_distance = 0;

	zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &h3_index, &k_distance);

	H3Index h = (H3Index)h3_index;

	if (h == PHP_H3_INVALID_INDEX) {
		RETURN_EMPTY_ARRAY();
	}

	if (k_distance < 0) {
		// h3-js treats values < 0 as 0.
		// h3-js.kRing(h3_index, -1) === h3-js.kRing(h3_index, 0)
		k_distance = 0;
	}

	int max_size = H3_EXPORT(maxKringSize)(k_distance);
	H3Index *out = (H3Index *)emalloc(sizeof(H3Index) * max_size);
	H3_EXPORT(kRing)(h, k_distance, out);

	int count = 0;

	for (int i = 0; i < max_size; ++i) {
		if (out[i]) {
			++count;
		}
	}

	array_init_size(return_value, count);
	count = 0;

	for (int i = 0; i < max_size; ++i) {
		if (out[i]) {
			add_index_long(return_value, count++, out[i]);
		}
	}

	efree(out);
	out = NULL;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_k_ring_distances, 0, 0, 2)
	ZEND_ARG_INFO(0, h3_index)
	ZEND_ARG_INFO(0, k_distance)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_k_ring_distances)
{
	zend_long h3_index;
	zend_long k_distance;

	zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &h3_index, &k_distance);

	if (k_distance < 0) {
		// h3-js v3.6.4
		// kRingDistances('invalid index', -1) => []
		// kRingDistances('ialid index', -1) => error
		RETURN_EMPTY_ARRAY();
	}

	H3Index h = (H3Index)h3_index;

	int *max_sizes = (int *)emalloc((k_distance + 1) * sizeof(int));

	for (int i = 0; i <= k_distance; ++i) {
		max_sizes[i] = H3_EXPORT(maxKringSize)(i);
	}

	int max_size = max_sizes[k_distance];
	H3Index *out = (H3Index *)emalloc(max_size * sizeof(H3Index));
	int distances[max_size];
	H3_EXPORT(kRingDistances)(h, k_distance, out, distances);

	int *counts = (int *)ecalloc(k_distance + 1, sizeof(int));
	H3Index *distance_ordered = (H3Index *)emalloc(max_size * sizeof(H3Index));

	for (int i = 0; i < max_size; ++i) {
		if (!out[i]) {
			continue;
		}

		int distance = distances[i];

		if (!distance) {
			distance_ordered[0] = out[i];
			counts[0] = 1;
			continue;
		}

		distance_ordered[max_sizes[distance - 1] + counts[distance]] = out[i];
		++counts[distance];
	}

	efree(out);
	out = NULL;

	array_init_size(return_value, k_distance + 1);

	zval ring;
	int ring_count = counts[0];

	array_init_size(&ring, ring_count);

	if (ring_count) {
		add_index_long(&ring, 0, distance_ordered[0]);
	}

	add_index_zval(return_value, 0, &ring);

	for (int i = 1; i <= k_distance; ++i) {
		zval ring;
		int ring_count = counts[i];
		int base_offset = max_sizes[i - 1];

		array_init_size(&ring, ring_count);

		for (int j = 0; j < ring_count; ++j) {
			add_index_long(&ring, j, distance_ordered[base_offset + j]);
		}

		add_index_zval(return_value, i, &ring);
	}

	efree(counts);
	counts = NULL;
	efree(max_sizes);
	max_sizes = NULL;
	efree(distance_ordered);
	distance_ordered = NULL;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_polyfill, 0, 0, 3)
	ZEND_ARG_INFO(0, coordinates)
	ZEND_ARG_INFO(0, holes)
	ZEND_ARG_INFO(0, resolution)
	ZEND_ARG_INFO(0, is_geo_json)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_polyfill)
{
	zval *coordinates;
	zval *holes;
	zend_long resolution;
	zend_bool is_geo_json = 0;

	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_ARRAY(coordinates)
		Z_PARAM_ARRAY_EX(holes, 1, 0)
		Z_PARAM_LONG(resolution)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(is_geo_json)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_EMPTY_ARRAY());

	if (resolution < 0 || resolution > PHP_H3_MAX_RESOLUTION) {
		// h3-js.polyfill() throws an Error('Invalid resolution: %d')
		php_error_docref(
			NULL,
			E_WARNING,
			"Expected parameter 3 (resolution) to be between 0 and %d, "
				"%ld given",
			PHP_H3_MAX_RESOLUTION,
			resolution
		);

		RETURN_EMPTY_ARRAY();
	}

	zend_long num_verts = zend_hash_num_elements(Z_ARRVAL_P(coordinates));

	if (!num_verts) {
		RETURN_EMPTY_ARRAY();
	}

	GeoCoord *verts = (GeoCoord *)emalloc(num_verts * sizeof(GeoCoord));
	zval *coord;
	zend_long idx = 0;

	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(coordinates), coord) {
		if (Z_TYPE_P(coord) == IS_ARRAY
			&& zend_hash_num_elements(Z_ARRVAL_P(coord)) == 2) {
			zval *zlat = zend_hash_index_find(
				Z_ARRVAL_P(coord),
				is_geo_json ? 1 : 0
			);
			zval *zlon = zend_hash_index_find(
				Z_ARRVAL_P(coord),
				is_geo_json ? 0 : 1
			);

			if (zend_parse_arg_double(zlat, &verts[idx].lat, NULL, 0)
				&& zend_parse_arg_double(zlon, &verts[idx].lon, NULL, 0)) {
				verts[idx].lat = H3_EXPORT(degsToRads)(verts[idx].lat);
				verts[idx].lon = H3_EXPORT(degsToRads)(verts[idx].lon);
				++idx;

				continue;
			}
		}

		efree(verts);
		verts = NULL;

		php_error_docref(
			NULL,
			E_WARNING,
			"Parameter 1 (coordinates) must be an array of [float, float]"
		);

		RETURN_EMPTY_ARRAY();
	} ZEND_HASH_FOREACH_END();

	GeoPolygon gp = {
		{ num_verts, verts },
		holes == NULL ? 0 : zend_hash_num_elements(Z_ARRVAL_P(holes)),
		NULL
	};

	gp.holes = (Geofence *)emalloc(gp.numHoles * sizeof(Geofence));

	if (gp.numHoles) {
		zval *hole;
		zend_long h_idx = -1;

		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(holes), hole) {
			if (Z_TYPE_P(hole) == IS_ARRAY) {
				num_verts = zend_hash_num_elements(Z_ARRVAL_P(hole));
				idx = 0;

				if (num_verts) {
					gp.holes[++h_idx] = (Geofence){
						num_verts,
						(GeoCoord *)emalloc(num_verts * sizeof(GeoCoord)),
					};

					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(hole), coord) {
						if (Z_TYPE_P(coord) == IS_ARRAY
							&& zend_hash_num_elements(Z_ARRVAL_P(coord)) == 2) {
							zval *zlat = zend_hash_index_find(
								Z_ARRVAL_P(coord),
								is_geo_json ? 1 : 0
							);
							zval *zlon = zend_hash_index_find(
								Z_ARRVAL_P(coord),
								is_geo_json ? 0 : 1
							);

							if (
								zend_parse_arg_double(
									zlat,
									&gp.holes[h_idx].verts[idx].lat,
									NULL,
									0
								)
								&&
								zend_parse_arg_double(
									zlon,
									&gp.holes[h_idx].verts[idx].lon,
									NULL,
									0
								)
							) {
								gp.holes[h_idx].verts[idx].lat
									= H3_EXPORT(degsToRads)(
										gp.holes[h_idx].verts[idx].lat
									);
								gp.holes[h_idx].verts[idx].lon
									= H3_EXPORT(degsToRads)(
										gp.holes[h_idx].verts[idx].lon
									);
								++idx;

								continue;
							}
						}
					} ZEND_HASH_FOREACH_END();
				}

				if (idx && idx >= num_verts) {
					continue;
				}
			}

			for (int i = 0; i <= h_idx; ++i) {
				efree(gp.holes[h_idx].verts);
			}

			efree(gp.holes);
			gp.holes = NULL;
			efree(verts);
			verts = NULL;

			php_error_docref(
				NULL,
				E_WARNING,
				"Parameter 2 (holes) must be an array of arrays of "
					"[float, float]"
			);

			RETURN_EMPTY_ARRAY();
		} ZEND_HASH_FOREACH_END();
	}

	int num_hexagons = H3_EXPORT(maxPolyfillSize)(&gp, resolution);
	H3Index* out = (H3Index*)ecalloc(num_hexagons, sizeof(H3Index));
	H3_EXPORT(polyfill)(&gp, resolution, out);

	for (int i = 0; i < gp.numHoles; ++i) {
		efree(gp.holes[i].verts);
		gp.holes[i].verts = NULL;
	}

	efree(gp.holes);
	gp.holes = NULL;
	efree(verts);
	verts = NULL;

	zend_long return_count = 0;

	for (int i = 0; i < num_hexagons; ++i) {
		if (out[i]) {
			++return_count;
		}
	}

	array_init_size(return_value, return_count);
	zend_long return_offset = 0;

	for (int i = 0; i < num_hexagons; ++i) {
		if (out[i]) {
			add_index_long(return_value, return_offset++, out[i]);
		}
	}

	efree(out);
	out = NULL;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_set_to_multi_polygon, 0, 0, 1)
	ZEND_ARG_INFO(0, coordinates)
	ZEND_ARG_INFO(0, as_geo_json)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_set_to_multi_polygon)
{
	zval *h3_indexes;
	zend_bool as_geo_json = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ARRAY(h3_indexes)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(as_geo_json)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_EMPTY_ARRAY());

	zend_long size = zend_hash_num_elements(Z_ARRVAL_P(h3_indexes));

	if (!size) {
		RETURN_EMPTY_ARRAY();
	}

	H3Index *hs = (H3Index *)emalloc(size * sizeof(H3Index));
	zend_long idx = 0;
	zval *h3_index;

	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(h3_indexes), h3_index) {
		zend_long h;

		if (!zend_parse_arg_long(h3_index, &h, NULL, 0, 0)) {
			efree(hs);
			hs = NULL;

			php_error_docref(
				NULL,
				E_WARNING,
				"Parameter 1 (h3_indexes) must be an array of int"
			);

			RETURN_EMPTY_ARRAY();
		}

		hs[idx++] = h;
	} ZEND_HASH_FOREACH_END();

	LinkedGeoPolygon out;
	H3_EXPORT(h3SetToLinkedGeo)(hs, size, &out);

	efree(hs);
	hs = NULL;

	LinkedGeoPolygon* polygon = &out;
	size = 0;

	while (polygon != NULL) {
		++size;
		polygon = polygon->next;
	}

	array_init_size(return_value, size);
	polygon = &out;
	idx = 0;

	while (polygon != NULL) {
		LinkedGeoLoop *loop = polygon->first;
		size = 0;

		while (loop != NULL) {
			++size;
			loop = loop->next;
		}

		zval z_loop;
		array_init_size(&z_loop, size);
		add_index_zval(return_value, idx++, &z_loop);

		loop = polygon->first;
		zend_long l_idx = 0;

		while (loop != NULL) {
			LinkedGeoCoord *coord = loop->first;
			size = 0;

			while (coord != NULL) {
				++size;
				coord = coord->next;
			}

			if (size) {
				zval z_coords;
				array_init_size(&z_coords, size + (as_geo_json ? 1 : 0));
				add_index_zval(&z_loop, l_idx++, &z_coords);

				coord = loop->first;
				zend_long c_idx = 0;

				while (coord != NULL) {
					zval z_latlon;
					array_init_size(&z_latlon, 2);
					add_index_zval(&z_coords, c_idx++, &z_latlon);

					if (as_geo_json) {
						add_index_double(
							&z_latlon,
							0,
							H3_EXPORT(radsToDegs)(coord->vertex.lon)
						);
						add_index_double(
							&z_latlon,
							1,
							H3_EXPORT(radsToDegs)(coord->vertex.lat)
						);
					} else {
						add_index_double(
							&z_latlon,
							0,
							H3_EXPORT(radsToDegs)(coord->vertex.lat)
						);
						add_index_double(
							&z_latlon,
							1,
							H3_EXPORT(radsToDegs)(coord->vertex.lon)
						);
					}

					coord = coord->next;
				}

				if (as_geo_json && size > 1) {
					coord = loop->first;
					zval z_latlon;
					array_init_size(&z_latlon, 2);
					add_index_zval(&z_coords, c_idx, &z_latlon);
					add_index_double(
						&z_latlon,
						0,
						H3_EXPORT(radsToDegs)(coord->vertex.lon)
					);
					add_index_double(
						&z_latlon,
						1,
						H3_EXPORT(radsToDegs)(coord->vertex.lat)
					);
				}
			}

			loop = loop->next;
		}

		polygon = polygon->next;
	}

	H3_EXPORT(destroyLinkedPolygon)(&out);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_to_geo, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_indexes)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_to_geo)
{
	zend_long h3_index = PHP_H3_INVALID_INDEX;

	zend_parse_parameters(ZEND_NUM_ARGS(), "l", &h3_index);

	H3Index h = (H3Index)h3_index;

	GeoCoord coord;

	H3_EXPORT(h3ToGeo)(h, &coord);

	array_init_size(return_value, 2);
	add_index_double(return_value, 0, H3_EXPORT(radsToDegs)(coord.lat));
	add_index_double(return_value, 1, H3_EXPORT(radsToDegs)(coord.lon));
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_to_geo_boundary, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_to_geo_boundary)
{
	zend_long h3_index = PHP_H3_INVALID_INDEX;

	zend_parse_parameters(ZEND_NUM_ARGS(), "l", &h3_index);

	H3Index h = (H3Index)h3_index;

	GeoBoundary boundary;
	H3_EXPORT(h3ToGeoBoundary)(h, &boundary);

	array_init_size(return_value, boundary.numVerts);

	for (int i = 0; i < boundary.numVerts; ++i) {
		zval latlng;
		array_init_size(&latlng, 2);
		add_index_double(
			&latlng, 0, H3_EXPORT(radsToDegs)(boundary.verts[i].lat)
		);
		add_index_double(
			&latlng, 1, H3_EXPORT(radsToDegs)(boundary.verts[i].lon)
		);
		add_index_zval(return_value, i, &latlng);
	}
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_h3_to_string, 0, 0, 1)
	ZEND_ARG_INFO(0, h3_index)
ZEND_END_ARG_INFO()

PHP_FUNCTION(h3_to_string)
{
	zend_long h3_index = PHP_H3_INVALID_INDEX;

	zend_parse_parameters(ZEND_NUM_ARGS(), "l", &h3_index);

	H3Index h = (H3Index)h3_index;

	char buff[17];

	H3_EXPORT(h3ToString)(h, buff, sizeof(buff));

	RETURN_STRING(buff);
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(h3)
{
	REGISTER_LONG_CONSTANT(
		"H3_MAX_RESOLUTION", PHP_H3_MAX_RESOLUTION, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_UNIT_KM", PHP_H3_UNIT_KM, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_UNIT_KM2", PHP_H3_UNIT_KM2, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_UNIT_M", PHP_H3_UNIT_M, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_UNIT_M2", PHP_H3_UNIT_M2, CONST_CS | CONST_PERSISTENT
	);

	char version[32];

	snprintf(
		version,
		sizeof(version),
		"%d.%d.%d",
		H3_VERSION_MAJOR,
		H3_VERSION_MINOR,
		H3_VERSION_PATCH
	);

	REGISTER_STRING_CONSTANT(
		"H3_VERSION", version, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_VERSION_MAJOR", H3_VERSION_MAJOR, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_VERSION_MINOR", H3_VERSION_MINOR, CONST_CS | CONST_PERSISTENT
	);

	REGISTER_LONG_CONSTANT(
		"H3_VERSION_PATCH", H3_VERSION_PATCH, CONST_CS | CONST_PERSISTENT
	);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(h3)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(h3)
{
#if defined(COMPILE_DL_H3) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(h3)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(h3)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "H3 Support", "enabled");

	char version[32];

	snprintf(
		version,
		sizeof(version),
		"%d.%d.%d",
		H3_VERSION_MAJOR,
		H3_VERSION_MINOR,
		H3_VERSION_PATCH
	);

	php_info_print_table_row(2, "H3 Library Version", version);
	php_info_print_table_end();
}
/* }}} */

/* {{{ h3_functions[]
 */
const zend_function_entry h3_functions[] = {
	PHP_FE(h3_distance, arginfo_h3_distance)
	PHP_FE(h3_edge_length, arginfo_h3_edge_length)
	PHP_FE(h3_from_geo, arginfo_h3_from_geo)
	PHP_FE(h3_from_string, arginfo_h3_from_string)
	PHP_FE(h3_get_base_cell, arginfo_h3_get_base_cell)
	PHP_FE(h3_get_faces, arginfo_h3_get_faces)
	PHP_FE(h3_get_resolution, arginfo_h3_get_resolution)
	PHP_FE(h3_hex_area, arginfo_h3_hex_area)
	PHP_FE(h3_is_pentagon, arginfo_h3_is_pentagon)
	PHP_FE(h3_is_res_class_iii, arginfo_h3_is_res_class_iii)
	PHP_FE(h3_is_valid, arginfo_h3_is_valid)
	PHP_FE(h3_is_valid_resolution, arginfo_h3_is_valid_resolution)
	PHP_FE(h3_is_valid_string, arginfo_h3_is_valid_string)
	PHP_FE(h3_k_ring, arginfo_h3_k_ring)
	PHP_FE(h3_k_ring_distances, arginfo_h3_k_ring_distances)
	PHP_FE(h3_polyfill, arginfo_h3_polyfill)
	PHP_FE(h3_set_to_multi_polygon, arginfo_h3_set_to_multi_polygon)
	PHP_FE(h3_to_geo, arginfo_h3_to_geo)
	PHP_FE(h3_to_geo_boundary, arginfo_h3_to_geo_boundary)
	PHP_FE(h3_to_string, arginfo_h3_to_string)

	PHP_FE_END
};
/* }}} */

/* {{{ h3_module_entry
 */
zend_module_entry h3_module_entry = {
	STANDARD_MODULE_HEADER,
	"h3",
	h3_functions,
	PHP_MINIT(h3),
	PHP_MSHUTDOWN(h3),
	PHP_RINIT(h3),
	PHP_RSHUTDOWN(h3),
	PHP_MINFO(h3),
	PHP_H3_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_H3
	#ifdef ZTS
		ZEND_TSRMLS_CACHE_DEFINE()
	#endif
	ZEND_GET_MODULE(h3)
#endif
