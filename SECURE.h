#ifndef COM_SECURE_H
#define COM_SECURE_H

#define ME "maker"
#define SECURITY_LOG "/w/"+ME+"/com/SECURITY.log"

private nomask int secure() {
  if(this_interactive() &&
    (string)this_interactive()->query_real_name() == "maker")
    return 1;
  else {
    notify_fail("Illegal action.\n");
    log_file(SECURITY_LOG, get_f_string("["+ ctime() +"] " +
      (string)this_interactive()->query_real_name() + " tried to use " +
      file_name()));
    return 0;
  }
}

#endif
