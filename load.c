#include <stdio.h>
#include <time.h>
#include <mysql.h>
#include <stdlib.h>

long double time_elapsed_msec(struct timeval begin_time, struct timeval end_time)
{
  return ((end_time.tv_sec - begin_time.tv_sec)*1000000 + (end_time.tv_usec - begin_time.tv_usec))/1000;
}

void error_msg(MYSQL *connection)
{
  printf("%s\n",mysql_error(connection));
  exit(1);
}
int main()
{
  MYSQL *connection, mysql;
  struct timeval begin, end;

  //set the connection
  mysql_init(&mysql);
  connection = mysql_real_connect(&mysql, "localhost", "root", "topsecret", "test" ,0,0,0);
  if(connection == NULL)
  {
    printf(mysql_error(&mysql));
    return 1;
  }
  //create table if not exsists
  if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS test.Testload(ID INT, MSG CHAR(15)) ENGINE=InnoDB;"))
  {
    printf(mysql_error(connection));
    return 1;
  }
  if(mysql_query(connection, "SET FOREIGN_KEY_CHECKS = 0;"))
  {
     printf(mysql_error(&mysql));
     return 1;
  }
  if(mysql_query(connection, "SET UNIQUE_CHECKS = 0;"))
  {
    error_msg(connection);
  }
  if(mysql_query(connection, "SET SESSION tx_isolation = 'READ-UNCOMMITTED'"))
  {
    error_msg(connection);
  }
  if(mysql_query(connection, "SET sql_log_bin = 0;"))
  {
    error_msg(connection);
  }
  char statement[]= "LOAD DATA INFILE '/home/plagueis/Projects/log' INTO TABLE Testload fields terminated by ' ' lines terminated by '\n'";
  gettimeofday(&begin,0);
  mysql_query(connection, statement);
  gettimeofday(&end,0);
  if(mysql_query(connection, "SET FOREIGN_KEY_CHECKS = 1;"))
  {
     printf(mysql_error(&mysql));
     return 1;
  }
  if(mysql_query(connection, "SET UNIQUE_CHECKS = 1;"))
  {
     error_msg(connection);
  }
  if(mysql_query(connection, "SET SESSION tx_isolation='READ-UNCOMMITTED'"))
  {
     error_msg(connection);
  }
  if(mysql_query(connection, "SET sql_log_bin = 1"))
  {
    error_msg(connection);
  }
  printf("Qeury time:  %.3Lf msec\n", time_elapsed_msec(begin,end));
 //close the connection
  mysql_close(connection);
}
