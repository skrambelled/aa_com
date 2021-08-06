#define TP        this_player()

main(str) {
    object ob;

    if(!str) {
        notify_fail("minherit <object>\n");
        return 0;
    }

    ob = present(str, TP);
    if (!ob) ob = present(str, environment(TP));
    if (!ob) {
        write("Cannot find "+str+" here.\n");
        return 1;
    }
    write("[Inheritance tree of object: "+file_name(ob)+"]\n");
    write(implode(inherit_list(ob), "\n")+"\n");
    return 1;
}

check(string name) { return 1; }
short_help() {
    return "Displays inheritance tree for <object>";
}
