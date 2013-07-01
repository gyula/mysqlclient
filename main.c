#include <stdio.h>
#include <mysql.h>
#include <my_global.h>

int main(int argc, char **argv)
{
 MYSQL_RES *result;
 MYSQL_ROW row;
 MYSQL *connection, mysql;
 int state;

//print out the installed MySQL client version
 printf("MySQL client version: %s\n", mysql_get_client_info());

//initialize the connection
 mysql_init(&mysql);
//set connection details
 connection = (&mysql,"localhost","root","topsecret","employees",0,0,0);
  if(connection == NULL)
  {
   printf(mysql_error(&mysql));
   return 1;
  }

//close connection
 mysql_close(connection);
}
