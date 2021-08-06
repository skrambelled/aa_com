#include <daemons.h>

inherit COLOURUTIL_D;

#define VALID_READ(X) "/secure/master"->valid_read(X,this_interactive()->query_real_name(),"")

static nomask int als(string dir);
string colour_table(string *files, string dir);


public nomask int main(string str) {
  int fsize;
  object player;
  
  seteuid(getuid());
  player = this_player();
  if(!str)
    str = player->query_path()+"/";
  else 
    str = (string)player->get_custom_path(player->query_path(), str);

  return als(str);
}

private nomask int als(string dir) {
  int i, size, highlight_begin, highlight_end, highlighting;
  int *ddates, ddate, *dsizes, dsize;
  int *fdates, fdate, *fsizes, fsize;
  string coloured_table;
  string *dnames, dname;
  string *fnames, fname;
  mixed files;
  
  if(dir[<1..<1] != "/")
    dir += "/";
  
  if(!VALID_READ(dir)) {
    writef("als: ["+dir+"] - invalid permissions, or no such directory.\n");
    return 1;
  }
    
  fsize = file_size(dir);
  if(fsize == -1) {
    writef("als: ["+dir+"] - No such directory.\n");
    return 1;
  }
  
  if(fsize > -1) {
    writef("als: ["+dir+"] - Target is file, not a directory.\n");
    return 1;
  }
  
  files = get_dir(dir, 7);
  
  dnames = ({});
  fnames = ({});
  dsizes = ({});
  fsizes = ({});
  ddates = ({});
  fdates = ({});
  
  // organize contents of dir into files and dirs
  for(i=0; i<sizeof(files); i+=3) {
    if(files[i+1] == -2) {
       dnames += ({files[i]+"/"});
       dsizes += ({files[i+1]});
       ddates += ({files[i+2]});
    } else {
       fnames += ({files[i]});
       fsizes += ({files[i+1]});
       fdates += ({files[i+2]});
    }
  }
  
  write_cf(red("Directory") + " of ["+cyan(dir)+"]");
  writef("Found "+sizeof(dnames)+" directories, "+sizeof(fnames)+" files.");
  
  coloured_table = colour_table(dnames, dir);
  if(strlen(coloured_table))
    write_c("\n"+coloured_table+"\n");
    
  coloured_table = colour_table(fnames, dir);
  if(strlen(coloured_table))
    write_c("\n"+coloured_table+"\n");
  
  return 1;
}

string colour_file(string file, string dir) {
  if(file[<1..<1] == "/")
    return iblue(file[0..<2]) + file[<1..<1];
  else if(file[<2..<1] == ".h")
    return yellow(file);
  else if(file[<2..<1] == ".c") {
    if(find_object(dir+file))
      return imagenta("*") + green(file);
    else
      return green(file);
  } else
    return file;
}

string colour_table(string *files, string dir) {
  int i, size, begin, end, colouring;
  string table, coloured_table;
  
  table = sprintf("%-80#s", implode(files,"\n"));
  coloured_table = "";
  
  size = strlen(table);
  for(i=0; i<size; i++) {
    if(!colouring) {
      if(table[i..i] == " " || table[i..i] == "\n" || i == size-1) {
        coloured_table += table[i..i];
      } else {
        colouring = 1;
        begin = i;
      }
    } else {
      if(table[i..i] == " " || table[i..i] == "\n" || i == size-1) {
        colouring = 0;
        if(i == size-1)
          i++;
        end = i-1;
        coloured_table += colour_file(table[begin..end], dir);
        // hack to account for offset in loaded .c files for '*' symbol
        if(table[i..i] != " " || !find_object(dir+table[begin..end]))
          coloured_table += table[i..i];
      }
    } 
  }
  return coloured_table;
}

check(string name) { return 1; }
short_help() { return "Alternate 'ls' command with ANSI."; }
long_help() { return "Syntax: als <path>\n"; }
