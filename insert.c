#include <stdio.h>
#include <time.h>
#include <mysql.h>

int main()
{
  MYSQL *connection, mysql;
  int i;
  //set the connection
  mysql_init(&mysql);
  connection = mysql_real_connect(&mysql, "localhost", "root", "topsecret", "test" ,0,0,0);
  if(connection == NULL)
  {
    printf(mysql_error(&mysql));
    return 1;
  }
  //create table if not exsists
  if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS test.Testinsert(ID INT, MSG CHAR(15));"))
  {
    printf(mysql_error(connection));
    return 1;
  }

  char statement[100];
  for(i=0; i < 100; i++)
  {
      snprintf(statement,100,"INSERT INTO Testinsert VALUES('%d','log_msg');",i);
  //printf("%s",statement);
      mysql_query(connection, statement);
  } 
 //close the connection
      mysql_close(connection);
}
