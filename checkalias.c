main(str) {
  int i;
  string *s, *t, a, b;
  mapping m;
  object o;
  
  if(!str)
    o = this_player();
  else {
    if(sscanf(str, "%s %s", a, b) != 2) 
      a = str;
    o = find_player(a);
  }
    
  if(!o) {
    notify_fail("Player: "+capitalize(a)+" not found.\n");
    return 0;
  }
  m = o->query_alias_list();
  s = m_indices(m);
  s = sort_array(s, #'>);
  if(b) {
    t = ({});
    for(i=0;i<sizeof(s);i++) {
      if(s[i][0..(strlen(b)-1)] == b)
      t += ({s[i]});
    }
    s = t;
  }
  t = ({"Aliases for "+o->query_name()+":\n"});
  for(i=0;i<sizeof(s);i++)
    t += ({s[i]+extract("           ",
      0, 10-strlen(s[i]))+" = "+m[s[i]]});
  this_player()->more(t);
  return 1;
}

check(string name) { return 1; }
short_help() { return "Displays a full alias list of a player."; }
long_help() { return "Syntax: checkalias <player>\n"; }