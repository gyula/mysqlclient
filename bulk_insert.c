#include <stdio.h>
#include <time.h>
#include <mysql.h>
#include <glib.h>

long double time_elapsed_msec(struct timeval begin_time, struct timeval end_time)
{
  return ((end_time.tv_sec - begin_time.tv_sec)*1000000 + (end_time.tv_usec - begin_time.tv_usec))/1000;
}

int main()
{
  MYSQL *connection, mysql;
  struct timeval begin, end;
  int i, max, j;
  GString *statement = g_string_new(NULL);
  GString *mymsg = g_string_new("log_msg");

  g_string_append(statement, "INSERT INTO Testinsert VALUES");
  max= 100000;
  //set the connection
  mysql_init(&mysql);
  connection = mysql_real_connect(&mysql, "localhost", "root", "topsecret", "test" ,0,0,0);
  if(connection == NULL)
  {
    printf(mysql_error(&mysql));
    return 1;
  }
  //create table if not exsists
  if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS test.Testinsert(ID INT, MSG CHAR(15)) ENGINE=InnoDB;"))
  {
    printf(mysql_error(connection));
    return 1;
  }

  if(mysql_query(connection, "SET autocommit=0;"))
  {
    printf(mysql_error(connection));
    return 1;
  }
  gettimeofday(&begin,0);
  for( i = 0  ; i < max; i++)
  {
    g_string_append(statement, g_strdup_printf("('%d','%s')",i,mymsg -> str));
    if( i < max-1 )
      {
        g_string_append(statement, ",");
      }
  }
  g_string_append(statement, ";");
  if(mysql_query(connection, statement -> str))
    {
      printf(mysql_error(connection));
      return 1;
    }
  if(mysql_query(connection, "COMMIT;"))
    {
      printf(mysql_error(connection));
      return 1;
    }
  gettimeofday(&end,0);
  printf("Query time:  %.3Lf msec\n", time_elapsed_msec(begin,end));
 //close the connection
  mysql_close(connection);
}
