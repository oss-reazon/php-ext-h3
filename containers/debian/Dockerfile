# borrowed from
# https://github.com/docker-library/php/blob/master/7.4/buster/cli/Dockerfile

FROM php:7.4.8-cli

RUN set -eux; \
	\
	savedAptMark="$(apt-mark showmanual)"; \
	apt-get update; \
	apt-get install -y --no-install-recommends \
		libargon2-dev \
		libcurl4-openssl-dev \
		libedit-dev \
		libonig-dev \
		libsodium-dev \
		libsqlite3-dev \
		libssl-dev \
		libxml2-dev \
		zlib1g-dev \
		valgrind \
		${PHP_EXTRA_BUILD_DEPS:-} \
	; \
	rm -rf /var/lib/apt/lists/*; \
	\
	export \
		CFLAGS="$PHP_CFLAGS" \
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
		-type f -executable -exec strip --strip-all '{}' + || \
		true \
	; \
	make clean; \
	cd /; \
	docker-php-source delete; \
	\
	# reset apt-mark's "manual" list so that "purge --auto-remove" will remove
	# all build dependencies
	apt-mark auto '.*' > /dev/null; \
	[ -z "$savedAptMark" ] || apt-mark manual $savedAptMark; \
	find /usr/local/php-debug -type f -executable -exec ldd '{}' ';' \
		| awk '/=>/ { print $(NF-1) }' \
		| sort -u \
		| xargs -r dpkg-query --search \
		| cut -d: -f1 \
		| sort -u \
		| xargs -r apt-mark manual \
	; \
	apt-get purge -y \
		--auto-remove \
		-o APT::AutoRemove::RecommendsImportant=false \
	; \
	\
	# setup build environment
	apt update; \
	apt-get install -y --no-install-recommends \
		autoconf \
		cmake \
		gcc \
		git \
		make \
		libtool \
		valgrind

ENV PATH /usr/local/php-debug/bin:$PATH
