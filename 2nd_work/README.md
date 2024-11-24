### Client and daemon apps which use mysyslog library

Use `make` to build a project
Use `make clean` to go back to source state 

After building a project you will get 2 executables files: log_client, log_daemon; 3 deb packages;

To use log_client you need to give it all options which it requires. You can read about them by running ./log_client. 
Log_daemon requires config file on path `/etc/mysyslog/mysyslog.cnf`

Example of config file:<br/>
MESSAGE=here you write your message<br/>
LEVEL=2<br/>
DRIVER=1<br/>
FORMAT=1<br/>
PATH=./path/to/file.txt<br/>

See `Libmysyslog/README.md` for better understanding of options
