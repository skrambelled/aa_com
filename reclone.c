#pragma strict_types

#define VALID_READ(X) "/secure/master"->valid_read(X,this_interactive()->query_real_name(),"")

inherit "obj/basic/create";

int main(string str) { 
  string filename, auto_load, *args, err;
  object ob, ob2;

  if(!str) {
    notify_fail("Usage: 'reclone <object id|path>'\n");
    return 0;
  }

  // if we have the path, we already have enough permissions to destruct
  if(ob = present(str, this_player()))
    filename = explode(file_name(ob), "#")[0];
  else {
    filename = (string)this_player()->get_custom_path(this_player()->query_path(), str);
    // Can't use reclone to guess at filenames without access
    if(!VALID_READ(filename)) {
      writef(filename=": Invalid read permissions.");
      return 1;
    }
  }
  
  // Make sure the file exists and is a .c file
  if(filename[<2..<1] != ".c")
    filename += ".c";
  writef("Recloning: "+filename);
  if(file_size(filename) < 0 || filename[<2..<1] != ".c") {
    writef(filename + " is not a valid file to load.");
    return 1;
  }

  // Destruct the blueprint to 'update' the object
  ob2 = find_object(filename);
  if(ob2)
    destruct(ob2);
  if(find_object(filename)) {
    write("Update failed.\n");
    return 1;
  }

  // Load and clone the new object
  if(err = catch(ob2 = clone_object(filename))) {
    writef("Clone failed: "+err+"\n");
    return 1;
  }

  // Move the new object
  ob2->move(this_player());
  if(environment(ob2) != this_player()) {
    write("Move failed.\n");
    destruct(ob2);
    return 1;
  }

  // apply any autoload args there might have been
  if(auto_load = (string)ob->query_auto_load()) {
    args = explode(auto_load, ":");
    if(sizeof(args) > 1)
      auto_load = implode(args[1..], ":");
    if(auto_load && auto_load != "" && function_exists("init_arg", ob2))
      ob2->init_arg(auto_load);
  }

  // Destruct the old object
  if(ob)
    destruct(ob);

  write("You reclone "+(string)ob2->short() + ".\n");
  return 1;
}

int check(string name) { return 1; }
string short_help() { return "Used to reclone objects."; }
string long_help() { return "Syntax: reclone <object id|path>\n"; }