QSServerApp
===========

Qt simple server application

get project:
```
$ git clone https://github.com/abcdw/QSServerApp.git
$ cd QSServerApp # project root
```

First command from any section below runs from project root

update project:
```
$ git pull
```

build:
```
$ mkdir build && cd build
$ qmake .. && make
```

create auth database and tables:
```
$ cd tools/sql
$ edit db/create_auth.sql # set strongpassword to your password
$ mysql -u root -p < db/create_auth.sql
$ mysql -u auth -pstrongpassword --database=auth < tables/auth.sql
```
run:
```
$ cd build
$ ./QSServerApp
```
