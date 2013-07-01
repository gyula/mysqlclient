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
 connection =mysql_real_connect (&mysql,"localhost","root","topsecret","employees",0,0,0);
  if(connection == NULL)
  {
   printf(mysql_error(&mysql));
   return 1;
  }
//check the query if there is an error the function will return a different value from 0
 state= mysql_query(connection, "SELECT * FROM employees");
  if(state != 0)
  {
   printf(mysql_error(connection));
   return 1;
  }
//store the result
 result = mysql_store_result(connection);
 printf("ROWS: %d\n", mysql_num_rows(result));
//close connection
 mysql_close(connection);
}
