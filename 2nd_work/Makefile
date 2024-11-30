client = mysyslog-client.c
daemon = mysyslog-daemon.c
library = Libmysyslog/*

APPS = mysyslog-client.c mysyslog-daemon.c Libmysyslog/libmysyslog.c
UNIT_FILE = /etc/systemd/system/mysyslog-daemon.service

version = 1.0
revision = 1
architecture = all

define DEB_create
	@mkdir -p MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-$(1)" 			>> MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 			>> MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)"	        >> MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>"  >> MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: $(1) app" 			>> MySyslog_$(1)_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_$(1)_${version}-${revision}_${architecture}/usr/Libmysyslog
	@cp $(client) MySyslog_$(1)_${version}-${revision}_${architecture}/usr
	@cp $(library) MySyslog_$(1)_${version}-${revision}_${architecture}/usr/Libmysyslog
	@dpkg-deb --root-owner-group --build MySyslog_$(1)_${version}-${revision}_${architecture}
endef

all: mysyslog_lib deb
	@cc $(APPS) -c
	@cc mysyslog-client.o libmysyslog.o -o log_client
	@cc mysyslog-daemon.o libmysyslog.o -o log_daemon

	@echo "\n\nRun 'make systemd_unit_file' to create unit file for systemd service"
	@echo "Run 'make astra_repo' to create a local apt repository\n"


astra_repo:
	@mkdir -p /usr/local/repos
	@cp *.deb /usr/local/repos
	@dpkg-scanpackages /usr/local/repos /dev/null | gzip -9c > /usr/local/repos/Packages.gz
	@echo "deb [trusted=yes] file:/usr/local/repos ./" > /etc/apt/sources.list.d/Mysyslog.list
	@sudo apt-get update
	@sudo apt-get install Mysyslog

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
	@cc Libmysyslog/libmysyslog-text.c -shared -o Libmysyslog/libmysyslog-text.so
	@cc Libmysyslog/libmysyslog-json.c -shared -o Libmysyslog/libmysyslog-json.so

deb: deb_daemon 
	$(call DEB_create,client)
	$(call DEB_create,library)

	@rm -fr MySyslog_*_${version}-${revision}_${architecture}

deb_daemon: $(daemon)
	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN
	@touch MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control

	@echo "Package: mysyslog-daemon" 					   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Version: $(version)" 						   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Architecture: $(architecture)" 					   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Maintainer: SPo101 <github.com/SPo101>" 				   >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control
	@echo "Description: Daemon app which uses mysysloglib library for logging" >> MySyslog_daemon_${version}-${revision}_${architecture}/DEBIAN/control

	@mkdir -p MySyslog_daemon_${version}-${revision}_${architecture}/{usr/Libmysyslog,etc/systemd/system}
	@cp $(daemon) MySyslog_daemon_${version}-${revision}_${architecture}/usr
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

clean:
	@rm -f Libmysyslog/*.o *.o
	@rm -f Libmysyslog/libmysyslog.so log_client log_daemon
	@rm -f Libmysyslog/libmysyslog-text.so Libmysyslog/libmysyslog-json.so
	@rm -fr MySyslog_*_${version}-${revision}_${architecture}*
