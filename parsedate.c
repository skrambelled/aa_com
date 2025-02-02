#pragma strict_types

int parse_date(string date_str);

int main(string str)
{
    int result;

    if (!str || (result = parse_date(str)) == -1)
    {
        writef("Invalid input format. See 'help parsedate' for details.");
        return 1;
    }

    write(result + "\n");
    return 1;
}

int check(string name) { return 1; }
string short_help() { return "Shows time() value of a give date."; }
string long_help() {
    return "Syntax: \n" +
        "  YYYY-MM-DD HH:MM:SS\n" +
        "  YYYY-MM-DD\n" +
        "  MM/DD/YYYY\n" +
        "  DD-MM-YYYY\n" +
        "  Month DD, YYYY\n" +
        "  DD Mon YYYY HH:MM:SS\n";
}

int is_leap_year(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int days_in_month(int month, int year) {
    int* days;
    days = ({ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 });

    if (month == 1 && is_leap_year(year)) {
        return 29; // February in a leap year
    }
    return days[month];
}

int days_since_epoch(int year, int month, int day) {
    int y, m, total_days;
    total_days = 0;

    // Days from 1970 to the given year
    for (y = 1970; y < year; y++) {
        total_days += is_leap_year(y) ? 366 : 365;
    }

    // Days from January to the given month
    for (m = 0; m < month; m++) {
        total_days += days_in_month(m, year);
    }

    // Add the given day
    total_days += day - 1;

    return total_days;
}

int parse_date(string date_str) {
    int year, month, day, hour, min, sec;
    string month_name;
    string* months;
    string* short_months;

    // Default time values if not provided
    hour = 0; min = 0; sec = 0;

    // YYYY-MM-DD or YYYY-MM-DD HH:MM:SS
    if (sscanf(date_str, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec) == 6 ||
        sscanf(date_str, "%d-%d-%d", year, month, day) == 3) {
        return days_since_epoch(year, month - 1, day) * 86400 + hour * 3600 + min * 60 + sec;
    }

    // MM/DD/YYYY
    if (sscanf(date_str, "%d/%d/%d", month, day, year) == 3) {
        return days_since_epoch(year, month - 1, day) * 86400 + hour * 3600 + min * 60 + sec;
    }

    // DD-MM-YYYY
    if (sscanf(date_str, "%d-%d-%d", day, month, year) == 3) {
        return days_since_epoch(year, month - 1, day) * 86400 + hour * 3600 + min * 60 + sec;
    }

    // Month DD, YYYY
    if (sscanf(date_str, "%s %d, %d", month_name, day, year) == 3) {
        months = ({ "january", "february", "march", "april", "may", "june",
                            "july", "august", "september", "october", "november", "december" });
        month = member_array(lower_case(month_name), months);
        if (month != -1) {
            return days_since_epoch(year, month, day) * 86400 + hour * 3600 + min * 60 + sec;
        }
    }

    // DD Mon YYYY HH:MM:SS
    if (sscanf(date_str, "%d %s %d %d:%d:%d", day, month_name, year, hour, min, sec) == 6) {
        short_months = ({ "jan", "feb", "mar", "apr", "may", "jun",
                                  "jul", "aug", "sep", "oct", "nov", "dec" });
        month = member_array(lower_case(month_name), short_months);
        if (month != -1) {
            return days_since_epoch(year, month, day) * 86400 + hour * 3600 + min * 60 + sec;
        }
    }

    return -1; // Return -1 if the format is not recognized
}
