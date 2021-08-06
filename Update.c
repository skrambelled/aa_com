#define TP this_player()

main(str) {
  string filename;
  object ob, ob2;
  
  seteuid(getuid());
  
  if(!str) {
    notify_fail("Usage: 'Update <object id|path>'\n");
    return 0;
  }
  if(ob = present(str, this_player()))
    filename = explode(file_name(ob), "#")[0];
  else
    filename = (string)TP->get_custom_path(TP->query_path(), str);
    
  ob2 = find_object(filename);
  if(ob2)
    destruct(ob2);
  if(ob2)
    write("Update: " + filename + " failed.\n");
  else
    write("Update: " + filename + " updated.\n");
  return 1;
}

check(string name) { return 1; }
short_help() { return "Used to update objects."; }
long_help() { return "Syntax: Update <object id|path>\n"; }