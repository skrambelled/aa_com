#pragma strict_types

#include <map.h>

#define TP this_player()

int check(string name) { return 1; }
string short_help() { return "Used to check mapdb settings at coordinates."; }
string long_help() { return "Syntax: 'mapsat' OR 'mapstat <x> <y>'\n"; }

int main(string s) { 
  int x, y, code;
      
  string output, path;
  object env, room;
  
  int land_type, land_sub, feat_type, feat_sub;
  string land_type_str, feat_type_str;

  seteuid(getuid());  
  
  env = environment(this_player());
  if(!env) {
    write("You have no enviroment!\n");
    return 1;
  }
  
  if(!s) {
    x = (int)env->query_x_coord();
    y = (int)env->query_y_coord();
  } else if(sscanf(s, "%d %d", x, y) != 2) {
    write(long_help());
    return 1;
  }
  
  path = (string)MAP_DB->query_inherit(x, y);
  
  // we need 5 vars for each coord set
  // the "path" which the coord inherits
  // then we need the code to get the other 4 vars:
  code = (int)MAP_DB->query_code(x, y);
    
  // extract vars
  land_type = LAND_TYPE(code);
  land_sub  = LAND_SUB(code);
  feat_type = FEAT_TYPE(code);
  feat_sub  = FEAT_SUB(code);
  
  land_type_str = ((string*)MAP_DB->query_landscapes())[land_type];
  feat_type_str = ((string*)MAP_DB->query_features())[feat_type];


  output = "("+x+","+y+")\n"
           "path      : " + path          + "\n" +
           "land_type : " + land_type     + " (" + land_type_str + ")\n" +
           "land_sub  : " + land_sub      + "\n" +
           "feat_type : " + feat_type     + " (" + feat_type_str + ")\n" +
           "feat_sub  : " + feat_sub      + "\n";
  
  write(output);
  return 1;
}
