main(str) {
  object o;
  int i, j;
  string *s, *t, r;
  t = ({});
  r = "";
  if(str)
   o = find_player(str);
  else
   o = this_player();
  if(!o)
  {
    notify_fail("No player: "+capitalize(o)+" found.\n");
    return 0;
  }
  s = query_actions(o);
  s = sort_array(s, #'>);
  for(i=0;i<sizeof(s);i++) {
    r += sprintf("%-15s", s[i]);
    if(j == 5) {
      t += ({r});
      r = "";
      j = 0;
    }
    j++;
  }
  write("Actions for: "+o->query_name()+".\n");
  this_player()->more(t);
  return 1;
}

check(string name) { return 1; }
short_help() { return "Shows the add_actions of a player."; }
long_help() { return "Syntax: checkactions <player>\n"; }