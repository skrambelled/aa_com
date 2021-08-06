#include <daemons.h>

inherit COLOURUTIL_D;

#define VALID_READ(X) "/secure/master"->valid_read(X,this_interactive()->query_real_name(),"")

check(string name) { return 1; }
short_help() { return "compare timestamps of two files."; }
long_help() { return "Syntax: timecompare <new file> <old file>\n"; }

public nomask int main(string str) {
  string file1, file2;
  int time1, time2;
  object player;

  seteuid(getuid());
  player = this_player();

  if(!str || sscanf(str, "%~s %~s %~s") == 3 ||
  sscanf(str, "%s %s", file1, file2) != 2) {
    write(long_help());
    return 1;
  }

  file1 = (string)player->get_custom_path(player->query_path(), file1);
  file2 = (string)player->get_custom_path(player->query_path(), file2);
  
  if(!VALID_READ(file1)) {
    writef(file1+" does not exist, or you do not have read permissions.");
    return 1;
  }

  if(!VALID_READ(file2)) {
    writef(file1+" does not exist, or you do not have read permissions.");
    return 1;
  }

  time1 = file_date(file1);
  time2 = file_date(file2);

  if(time1 < 0) {
    writef(file1+" does not exist or is a directory.");
    return 1;
  }

  if(time2 == 0) {
    writef(file2+" does not exist or is a directory.");
    return 1;
  }

  if(time1 > time2)
    COLOURUTIL_D->write_cf(igreen(file1 + " age is newer than " + file2));
  else if(time1 < time2)
    COLOURUTIL_D->write_cf(ired(file1 + " age is older than " + file2));
  else
    COLOURUTIL_D->write_cf(iyellow(file1 + " age is equal to " + file2));

  return 1;
}
