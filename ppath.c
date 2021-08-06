#define ENVTP environment(this_player())

void report_success(string *path);
void report_failure();

main(str) {
  if(!str || !find_object(str)) {
    notify_fail("Either you didn't type the room or it isn't loaded.\n");
    return 0;
  } else {
    find_object("/w/adinos/public/pathfinder/pathd")->find_path(ENVTP,
      find_object(str),this_object());
    return 1;
  }
}

void report_success(string *path) {
  tell_object(find_player("maker"), "Path: "+implode(path,", ")+"\n");
}

void report_failure() {
  tell_object(find_player("maker"), "Failed to find a path.\n");
}

check(string name) { return 1; }
short_help() { return "Checks the path for persona NPC's"; }
long_help() { return "Syntax: persona <room>\n"; }
