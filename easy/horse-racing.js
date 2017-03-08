var N = parseInt(readline());
var horses = [];
for (var i = 0; i < N; i++) {
    var pi = parseInt(readline());
    horses.push(pi);
}
horses.sort(compare);
printErr(horses);
min = horses[horses.length-1];
for(var i = 1; i < horses.length; i++){
    var a = horses[i-1];       
    var b = horses[i];
    if(b - a <= min && b > 0)
    {
        min = b - a;
    }
}

print(min);
function compare(a,b)
{
    if(a < b)
        return -1;
    else
        return 1;
        
    return 0;
}