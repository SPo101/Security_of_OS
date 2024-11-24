client = mysyslog-client.c
daemon = mysyslog-daemon.c
library = Libmysyslog/*
version = 1.0
revision = 1
architecture = all

all: mysyslog_lib deb
	@cc $(client) -o log_client
	@cc $(daemon) -o log_daemon

mysyslog_lib:
	@cc Libmysyslog/libmysyslog.c -shared -o Libmysyslog/libmysyslog.so
	@cc Libmysyslog/libmysyslog-text.c -shared -o Libmysyslog/libmysyslog-text.so
	@cc Libmysyslog/libmysyslog-json.c -shared -o Libmysyslog/libmysyslog-json.so

deb: deb_client deb_daemon deb_lib

deb_client: $(client)
	@mkdir MySyslog_client_${version}-${revision}_${architecture}
	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-client" 					   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 						   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)" 					   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 				   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Client app which uses mysysloglib library for logging" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/usr
	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/usr/Libmysyslog
	@cp $(client) MySyslog_client_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_client_${version}-${revision}_${architecture}/usr/Libmysyslog
	@dpkg-deb --root-owner-group --build MySyslog_client_${version}-${revision}_${architecture}

deb_daemon:
	@mkdir MySyslog_daemon_${version}-${revision}_${architecture}
	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-daemon" 					   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 						   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)" 					   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 				   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Daemon app which uses mysysloglib library for logging" >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/usr
	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/usr/Libmysyslog
	@cp $(client) MySyslog_daemon_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_daemon_${version}-${revision}_${architecture}/usr/Libmysyslog
	@dpkg-deb --root-owner-group --build MySyslog_daemon_${version}-${revision}_${architecture}

deb_lib:
	@mkdir MySyslog_library_${version}-${revision}_${architecture}
	@mkdir -p MySyslog_library_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-library" 		  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 			  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)"   	  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 	  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Mysyslog library for logging" >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_library_${version}-${revision}_${architecture}/usr
	@mkdir -p MySyslog_library_${version}-${revision}_${architecture}/usr/Libmysyslog
	@cp $(client) MySyslog_library_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_library_${version}-${revision}_${architecture}/usr/Libmysyslog
	@dpkg-deb --root-owner-group --build MySyslog_library_${version}-${revision}_${architecture}

clean:
	@rm -f Libmysyslog/libmysyslog.so log_client log_daemon
	@rm -f Libmysyslog/libmysyslog-text.so Libmysyslog/libmysyslog-json.so
	@rm -fr MySyslog_client_${version}-${revision}_${architecture}*
	@rm -fr MySyslog_daemon_${version}-${revision}_${architecture}*
	@rm -fr MySyslog_library_${version}-${revision}_${architecture}*
