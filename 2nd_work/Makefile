client = mysyslog-client.c
library = Libmysyslog/libmysyslog.c
version = 1.0
revision = 1
architecture = all

all: mysyslog_lib | deb_client
	@cc $(client) -o log_client

mysyslog_lib:
	@cc Libmysyslog/libmysyslog.c -shared -o Libmysyslog/libmysyslog.so

deb_client: $(client)
	@mkdir MySyslog_client_${version}-${revision}_${architecture}
	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Package: mysyslog-client" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <@gmail.com>" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Client app which uses mysysloglib library for logging" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/usr
	@cp $(client) MySyslog_client_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_client_${version}-${revision}_${architecture}/usr
	@dpkg-deb --root-owner-group --build MySyslog_client_${version}-${revision}_${architecture}

deb_daemon:
deb_lib:

clean:
	@rm -f Libmysyslog/libmysyslog.so log_client
	@rm -fr MySyslog_client_${version}-${revision}_${architecture}*
