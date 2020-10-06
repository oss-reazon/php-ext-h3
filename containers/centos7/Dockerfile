FROM centos:7.8.2003

ENV GPG_KEYS="42670A7FE4D0441C8E4632349E4FDC074A4EF02D 5A52880781F755608BF815FC910DEB46F53EA312" \
	PHP_VERSION="7.4.8" \
	PHP_URL="https://www.php.net/distributions/php-7.4.8.tar.xz" \
	PHP_ASC_URL="https://www.php.net/distributions/php-7.4.8.tar.xz.asc" \
	PHP_SHA256="642843890b732e8af01cb661e823ae01472af1402f211c83009c9b3abd073245" \
	PHP_CFLAGS="-fstack-protector-strong -fpic -fpie -D_FILE_OFFSET_BITS=64" \
	PHP_LDFLAGS="-Wl,-O1 -pie"

ENV PHP_CPPFLAGS="$PHP_CFLAGS"

RUN set -eux; \
	\
	yum -y install \
		https://repo.ius.io/ius-release-el7.rpm \
		https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm \
	; \
	\
	# setup PHP v7.4
	yum -y install \
		mod_php74 \
		php74-bcmath \
		php74-cli \
		php74-common \
		php74-devel \
		php74-gd \
		php74-json \
		php74-mbstring \
		php74-mysqlnd \
		php74-opcache \
		php74-pdo \
		php74-pecl-apcu \
		php74-pecl-igbinary \
		php74-pecl-memcached \
		php74-pecl-redis \
		php74-process \
		php74-xml \
	; \
	\
	# setup PHP debug build
	yum -y install make oniguruma-devel sqlite-devel valgrind-devel; \
	curl -fsSL -o php.tar.xz "$PHP_URL"; \
	echo "$PHP_SHA256 *php.tar.xz" | sha256sum -c -; \
	curl -fsSL -o php.tar.xz.asc "$PHP_ASC_URL"; \
	export GNUPGHOME="$(mktemp -d)"; \
	for key in $GPG_KEYS; do \
		gpg --batch --keyserver ha.pool.sks-keyservers.net --recv-keys "$key"; \
	done; \
	gpg --batch --verify php.tar.xz.asc php.tar.xz; \
	rm -rf "$GNUPGHOME"; \
	mkdir php; \
	tar -xJf php.tar.xz -C php --strip-components=1; \
	cd php; \
	export CFLAGS="$PHP_CFLAGS" \
		CPPFLAGS="$PHP_CPPFLAGS" \
		LDFLAGS="$PHP_LDFLAGS" \
	; \
	./configure \
		--with-config-file-path=/usr/local/php-debug/etc \
		--with-config-file-scan-dir=/usr/local/php-debug/etc/php.d \
		--enable-option-checking=fatal \
		--enable-mbstring \
		--enable-mysqlnd \
		--prefix=/usr/local/php-debug \
		--program-suffix=-debug \
		--enable-debug \
		--with-valgrind \
	; \
	make -j "$(nproc)"; \
	find -type f -name '*.a' -delete; \
	make install; \
	mkdir /usr/local/php-debug/etc; \
	cp /etc/php.ini /usr/local/php-debug/etc/; \
	find /usr/local/php-debug/bin /usr/local/php-debug/sbin \
		-type f -perm +0111 -exec strip --strip-all '{}' + || \
		true \
	; \
	cd ..; \
	rm -rf php php.tar.xz; \
	\
	# setup build envrionment
	yum -y install \
		autoconf \
		cmake3 \
		gcc \
		git \
		libtool \
		make \
		valgrind \
		which \
	; \
	\
	# for debug
	sed -i 's/^enable_dl = Off/enable_dl = On/' /etc/php.ini

ENV PATH /usr/local/php-debug/bin:$PATH

CMD ["php", "-a"]
