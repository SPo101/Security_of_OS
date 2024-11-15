file = mysyslog-client.c

all: mysyslog_lib
	@cc $(file) -o log_client

mysyslog_lib:
	@cc libmysyslog.c -shared -o libmysyslog.so

deb_dir:

clean:
	@rm libmysyslog.so log_client
