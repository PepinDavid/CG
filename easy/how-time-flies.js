/** 50% reussite
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
replaceAll = function(target, search, replacement) {
    return target.replace(new RegExp(search, 'g'), replacement);
}
var BEGIN = new Date(readline().split(".").reverse().join("/"));
var END = new Date(readline().split(".").reverse().join("/"));

printErr(BEGIN);
printErr(END);

// Write an action using print()
// To debug: printErr('Debug messages...');
var monthDiff = Math.abs(END.getMonth() - BEGIN.getMonth());
var yearDiff = Math.abs(END.getYear() - BEGIN.getYear());
var daysDiff = Math.ceil(Math.abs(END.getTime() - BEGIN.getTime()) / (1000 * 3600 * 24));
var s = "";
if(yearDiff > 0){
    if(yearDiff == 1)
        s += yearDiff+" year, ";
    else
        s += yearDiff+" years, ";
}
if(monthDiff > 0){
    if(monthDiff == 1)
        s += monthDiff+" month, ";
    else
        s += monthDiff+" months, ";
}
if(daysDiff == 1)
    s += "total "+daysDiff+" day";
else
    s += "total "+daysDiff+" days";
print(s);
