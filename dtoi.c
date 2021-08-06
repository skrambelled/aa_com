status is_leap_year(int year)
{
  if(year % 400 == 0) return 1;
  else if(year % 100 == 0) return 0;
  else if(year % 4 == 0) return 1;
  else return 0;
}

main(str) {
  int i;
  int day, month, year;
  status leap;
  string mon;
  
  if(sscanf(str, "%d %s %d", day, mon, year) != 3 || year < 1970) {
    write("Syntax: day month year... '10 Oct 2010'\n");
    return 0;
  }
  leap = is_leap_year(year);
  for(i = year - 1; i > 1970; i--){
    if(is_leap_year(i))
      day++;
  }
  year -= 1970;
  year *= (365*24*60*60);
  switch(lower_case(mon[0..2])){
    case "dec": month += (30*24*60*60); //nov
    case "nov": month += (31*24*60*60); //oct
    case "oct": month += (30*24*60*60); //sep
    case "sep": month += (31*24*60*60); //aug
    case "aug": month += (31*24*60*60); //jul
    case "jul": month += (30*24*60*60); //jun
    case "jun": month += (31*24*60*60); //may
    case "may": month += (30*24*60*60); //apr
    case "apr": month += (31*24*60*60); //mar
    case "mar": month += (28*24*60*60); if(leap) day++; //feb
    case "feb": month += (31*24*60*60); //jan
    case "jan": break;
  }
  day *= (24*60*60);
  if(day)
    day -= (24*60*60);
  write(day+month+year+"\n");
  return 1;
}

check(string name) { return 1; }
short_help() { return "Shows time() value of a give date."; }
long_help() { return "Syntax: day month year... '10 Oct 2010'\n"; }