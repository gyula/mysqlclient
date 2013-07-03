#include <stdio.h>
#include <mysql.h>
#include <my_global.h>
#include <time.h>
long double time_elapsed_msec(struct timeval begin_time, struct timeval end_time)
{
  return ((end_time.tv_sec - begin_time.tv_sec)*1000000 + (end_time.tv_usec - begin_time.tv_usec))/1000;
}
int main(int argc, char **argv)
{
 MYSQL_RES *result;
 MYSQL_ROW row;
 MYSQL *connection, mysql;
 int state,i;
 struct timeval begin, end;
 int num_fields;
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
 gettimeofday(&begin,0);
 state= mysql_query(connection, "SELECT * FROM employees WHERE first_name = 'Patricia'");
  if(state != 0)
  {
   printf(mysql_error(connection));
   return 1;
  }
//store the result
 result = mysql_store_result(connection);
 num_fields = mysql_num_fields(result);
 while((row = mysql_fetch_row(result)) != NULL )
 {
  for(i = 0; i < num_fields; i++)
   {
     printf("%-15s ",(row[i] ? row[i] : NULL));
   }
     printf("\n");
 }
 printf("ROWS: %d\n", mysql_num_rows(result));
 gettimeofday(&end,0);
 printf("Qeury time:  %.3Lf msec\n", time_elapsed_msec(begin,end));
//free the result
 mysql_free_result(result);
//close connection
 mysql_close(connection);
}
