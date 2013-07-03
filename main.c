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
 state= mysql_query(connection, "SELECT emp_no, first_name, last_name FROM employees WHERE first_name = 'Patricia'");
  if(state != 0)
  {
   printf(mysql_error(connection));
   return 1;
  }
//store the result
 result = mysql_store_result(connection);
 while((row = mysql_fetch_row(result)) != NULL )
 {
  printf(" %d  %s  %s\n",(row[0] ? row[0] : NULL), (row[1] ? row[1] : NULL), (row[2] ? row[2] : NULL));
 }
 printf("ROWS: %d\n", mysql_num_rows(result));
//free the result
 mysql_free_result(result);
//close connection
 mysql_close(connection);
}
