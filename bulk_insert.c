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
  char statement[4000];
  char insert[] = "INSERT INTO Testinsert(ID,MSG) VALUES";
  char id[10];
  char msg[] = " ,'log_msg'";
  char leftb[] = " (";
  char rightb[] = ")";
  char coma[] = ",";
  char coma2[] = ";";

  max= 200;
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

  if(mysql_query(connection, "BEGIN"))
  {
    printf(mysql_error(connection));
    return 1;
  }
  gettimeofday(&begin,0);
  for( j = 0 ; j < 50; j++)
  {
    strcpy(statement, insert);

   for( i = 0 ; i < max ; i++)
   {
    snprintf(id,sizeof id, "'%d'", i );
    strcat(statement, leftb);
    strcat(statement, id);
    strcat(statement, msg);
    strcat(statement, rightb);
     if(i < max-1)
     {
       strcat(statement, coma);
     }
   }
   strcat(statement, coma2);
   // printf("%s\n", statement);
   if(mysql_query(connection, statement))
   {
    printf(mysql_error(connection));
    return 1;
   }
   if(mysql_query(connection, "COMMIT;"))
   {
    printf(mysql_error(connection));
    return 1;
   }
  }
  gettimeofday(&end,0);
  printf("Qeury time:  %.3Lf msec\n", time_elapsed_msec(begin,end));
 //close the connection
  mysql_close(connection);
}
