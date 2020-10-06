# borrowed from
# https://github.com/docker-library/php/blob/master/7.4/alpine3.12/cli/Dockerfile

FROM php:7.4.8-cli-alpine3.12

RUN set -eux; \
	apk add --no-cache --virtual .build-deps \
		$PHPIZE_DEPS \
		argon2-dev \
		coreutils \
		curl-dev \
		libedit-dev \
		libsodium-dev \
		libxml2-dev \
		linux-headers \
		oniguruma-dev \
		openssl-dev \
		sqlite-dev \
		valgrind-dev \
	; \
	export CFLAGS="$PHP_CFLAGS" \
		CPPFLAGS="$PHP_CPPFLAGS" \
		LDFLAGS="$PHP_LDFLAGS" \
	; \
	docker-php-source extract; \
	cd /usr/src/php; \
	$(php -i | \
		grep '^Configure Command =>' | \
		sed 's/^Configure Command =>  //' | \
		sed "s/'//g") \
		--prefix=/usr/local/php-debug \
		--program-suffix=-debug \
		--enable-debug \
		--with-valgrind \
	; \
	make -j "$(nproc)"; \
	find -type f -name '*.a' -delete; \
	make install; \
	find /usr/local/php-debug/bin /usr/local/php-debug/sbin \
		-type f -perm +0111 -exec strip --strip-all '{}' + || \
		true \
	; \
	make clean; \
	cd /; \
	docker-php-source delete; \
	runDeps="$( \
		scanelf --needed --nobanner --format '%n#p' --recursive /usr/local/php-debug \
			| tr ',' '\n' \
			| sort -u \
			| awk 'system("[ -e /usr/local/php-debug/lib/" $1 " ]") == 0 { next } { print "so:" $1 }' \
	)"; \
	apk add --no-cache $runDeps; \
	\
	apk del --no-network .build-deps; \
	\
	apk add autoconf cmake gcc git libtool make musl-dev valgrind

ENV PATH /usr/local/php-debug/bin:$PATH
