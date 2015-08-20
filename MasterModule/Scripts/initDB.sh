#!/bin/sh

pwd=`pwd`
toDo=`cat $pwd/SQL/odb_schema.sql && cat $pwd/SQL/sample.sql`
mysql --user=powermonitor --password=powermonitor powermonitor <<EOF
$toDo
EOF
