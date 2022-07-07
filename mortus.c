#pragma strict_types
#include <calendar.h>

#define SAVEDIR "/w/adinos/misc/coroner/save/"

int check(string name) { return 1; }
string short_help() { return "Used to see real dates of mortus logs."; }
string long_help() { return "Syntax: 'mortus <playername>'\n"; }

string get_date(int y, string month, int d) {
  string date;
  int m;
  
  m = member(CALENDAR_HE_MONTH_NAMES, month)+1;
  
  date = ctime((((((y-350)*12)+(m-1))*28)+(d-1))*24*60*10);
  
  return date[0..9]+", "+date[20..23];
}

void list_deaths(string s1, string s2, string file) {
  string *deaths, de, month, spam;
  int i, j, year, day;
  
  deaths = explode(regreplace(regreplace(read_file(file),"#",s2,1),"="," "+s1+" [",1),"\n");
  
  de = "";
  for(i=0, j=sizeof(deaths); i<j; i++) {
    sscanf(deaths[i], "  On %s %d, %d %s", month, day, year, spam);
    de += get_f_string("  On "+get_date(year, month, day)+" "+spam, 0, 4);
  }
  deaths = explode(de, "\n");

  write("Mortus tells you: Looking through my lists of deaths, I find:\n");
  this_player()->more(deaths);
}

int main(string s) {
  string deathfile;

  seteuid(getuid());
  
  if(!s) {
    notify_fail("mortus who?\n");
    return 0;
  }
  
  s = lower_case(s);
  deathfile = SAVEDIR+s[0..0]+"/"+s;
  
  if(file_size(deathfile) == -1)
    writef("No deaths recorded for '"+s+"'.");
  else
    list_deaths(capitalize(s),"] was ",deathfile);
  
  return 1;
}
