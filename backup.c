#pragma strict_types

#include <daemons.h>

#define TP this_player()
#define VALID_READ(X) "/secure/master"->valid_read(X,this_interactive()->query_real_name(),"")
#define VALID_WRITE(X) "/secure/master"->valid_write(X,this_interactive()->query_real_name(),"")

string my_month(string month_str) {
  switch(month_str) {
    case "Jan": return "01";
    case "Feb": return "02";
    case "Mar": return "03";
    case "Apr": return "04";
    case "May": return "05";
    case "Jun": return "06";
    case "Jul": return "07";
    case "Aug": return "08";
    case "Sep": return "09";
    case "Oct": return "10";
    case "Nov": return "11";
    case "Dec": return "12";
    default   : return "00";
  }
}

int main(string str) { 
  string file, newfile, year, month, day;
  
  seteuid(getuid());  
  
  if(!str) {
    notify_fail("Usage: 'backup <path>'\n");
    return 0;
  }

  file = (string)TP->get_custom_path(TP->query_path(), str);
  
  if(!VALID_READ(file)) {
    write("Invalid read permissions.\n");
    return 1;
  }
  
  if(!VALID_WRITE(file)) {
    write("Invalid write permissions.\n");
    return 1;
  }
  
  // verify the file exists
  if(file_size(file) < 0) {
    write("No such file: " + file + "\n");
    return 1;
  }
  
  if(file_size(file) >= 50000) {
    write("Too large file: " +file+ "\n");
    return 1;
  }
  
  // collect our date info
  year  = ctime()[20..<1];
  month = my_month(ctime()[4..6]);
  day   = ctime()[8..9];
  
  // account for whitespace in the day of the month int
  if(day[0..0] == " ")
    day[0..0] = "0";
    
  newfile = file;
  
  // strip ".c" if applicable, otherwise keep the extension (like a .h)
  if(strlen(newfile) > 2 && newfile[<2..<1] == ".c")
    newfile = newfile[0..<3];
 
  newfile = newfile + "." + year + month + day + "." +
            (string)TP->query_real_name();
  
  // clean up our backup file location          
  rm(newfile);
  
  // now lets write a backup
  write_file(newfile, read_bytes(file, 0, file_size(file)));
  
  write("Backup 1 file.\n");
  return 1;
}

int check(string name) { return 1; }
string short_help() { return "Used to backup files."; }
string long_help() { return "Syntax: backup <path>\n"; }