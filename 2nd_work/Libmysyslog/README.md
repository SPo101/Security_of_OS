### Library for logging - libmysyslog.c
### Drivers for library - libmysyslog-text.c, libmysyslog-json.c
- libmysyslog-text.c - log output as a delimited string
- libmysyslog-json.c - log output as a json string

Library provides `mysyslog` function for logging.\
API of mysyslog: ```int mysyslog(const char* msg, int level, int driver, int format, const char* path)```\
args:\
1. msg - message we want to write into log file
2. level - level of message: 1-DEBUG 2-INFO 3-WARNING 4-ERROR 5-CRITICAL
3. driver - driver we gonna use; in this realization 0 for text driver, 1 for json driver
4. format - format of logging; in this realization we dont use it, so you can give it any number, it doesnt make sence
5. path - path to file to log or default for logging into `/var/log/syslog`
