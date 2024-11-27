client = mysyslog-client.c
daemon = mysyslog-daemon.c
library = Libmysyslog/*

UNIT_FILE = /etc/systemd/system/mysyslog-daemon.service

version = 1.0
revision = 1
architecture = all

all: mysyslog_lib deb
	@cc $(client) -o log_client
	@cc $(daemon) -o log_daemon
	@echo "\n\nRun 'make systemd_unit_file' to create unit file for systemd service\n"

systemd_unit_file:
	@touch $(UNIT_FILE) 
	@chmod 664 $(UNIT_FILE)
	@echo "[Unit]"						  >> $(UNIT_FILE)
	@echo "Description=Daemon, wich logs info via mysyslog\n" >> $(UNIT_FILE)
	@echo "[Service]"					  >> $(UNIT_FILE)
	@echo "ExecStart=/usr/log_daemon"			  >> $(UNIT_FILE)
	@echo "Type=forking"					  >> $(UNIT_FILE)
	@echo "PIDFile=/usr/run/mysyslog-daemon.pid\n"		  >> $(UNIT_FILE)
	@echo "[Install]"					  >> $(UNIT_FILE)
	@echo "WantedBy=multi-user.target"			  >> $(UNIT_FILE)

mysyslog_lib:
	@cc Libmysyslog/libmysyslog.c -shared -o Libmysyslog/libmysyslog.so
	@cc Libmysyslog/libmysyslog-text.c -shared -o Libmysyslog/libmysyslog-text.so
	@cc Libmysyslog/libmysyslog-json.c -shared -o Libmysyslog/libmysyslog-json.so

deb: deb_client deb_daemon deb_lib
	@rm -fr MySyslog_client_${version}-${revision}_${architecture}
	@rm -fr MySyslog_daemon_${version}-${revision}_${architecture}
	@rm -fr MySyslog_library_${version}-${revision}_${architecture}

deb_client: $(client)
	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-client" 					   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 						   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)" 					   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 				   >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Client app which uses mysysloglib library for logging" >> MySyslog_client_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_client_${version}-${revision}_${architecture}/usr/Libmysyslog
	@cp $(client) MySyslog_client_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_client_${version}-${revision}_${architecture}/usr/Libmysyslog
	@dpkg-deb --root-owner-group --build MySyslog_client_${version}-${revision}_${architecture}

deb_daemon:
	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-daemon" 					   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 						   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)" 					   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 				   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Daemon app which uses mysysloglib library for logging" >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/{usr/Libmysyslog,etc/systemd/system}
	@cp $(client) MySyslog_daemon_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_daemon_${version}-${revision}_${architecture}/usr/Libmysyslog

	@touch MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE) 
	@chmod 664 MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "[Unit]"						  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "Description=Daemon, wich logs info via mysyslog\n" >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "[Service]"					  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "ExecStart=/usr/log_daemon"			  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "Type=forking"					  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "PIDFile=/usr/run/mysyslog-daemon.pid\n"		  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "[Install]"					  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)
	@echo "WantedBy=multi-user.target"			  >> MySyslog_daemon_${version}-${revision}_${architecture}/$(UNIT_FILE)

	@dpkg-deb --root-owner-group --build MySyslog_daemon_${version}-${revision}_${architecture}

deb_lib:
	@mkdir -p MySyslog_library_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-library" 		  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 			  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)"   	  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 	  >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Mysyslog library for logging" >> MySyslog_library_${version}-${revision}_${architecture}/DEBIAN/control

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
