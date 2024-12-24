/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var n = parseInt(readline());
var t = 0;
for(var i = 1; i <= n; i++){
    var j = ~~(n / i);
    t += i*j;
}

print(t);