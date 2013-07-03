#include <stdio.h>
#include <time.h>
#include <mysql.h>

int main()
{
 MYSQL *connection, mysql;

 //set the connection
 mysql_init(&mysql);
 connection = mysql_real_connect(&mysql, "localhost", "root", "topsecret", "test" ,0,0,0);
 if(connection == NULL)
  {
   printf(mysql_error(&mysql));
   return 1;
  }

//close the connection
 mysql_close(connection);
}
