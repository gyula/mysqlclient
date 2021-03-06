#include <stdio.h>
#include <time.h>
#include <mysql.h>

long double time_elapsed_msec(struct timeval begin_time, struct timeval end_time)
{
  return ((end_time.tv_sec - begin_time.tv_sec)*1000000 + (end_time.tv_usec - begin_time.tv_usec))/1000;
}

int main()
{
  MYSQL *connection, mysql;
  struct timeval begin, end; 
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
  if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS test.Testinsert(ID INT, MSG CHAR(15)) ENGINE=InnoDB;"))
  {
    printf(mysql_error(connection));
    return 1;
  }

  char statement[50];
  gettimeofday(&begin,0);
  if(mysql_query(connection, "Begin"))
  {
    printf(mysql_error(connection));
    return 1;
  }
  for(i=0; i < 10000; i++)
  {
      snprintf(statement,50,"INSERT INTO Testinsert VALUES('%d','log_msg');",i);
  //printf("%s",statement);
      mysql_query(connection, statement);
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
