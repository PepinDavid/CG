/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var N = parseInt(readline());
var arr = [];
var etg2 = [];
for(var i = 0; i < N; i++){
    var a = new Array(N).fill(" ");
    if(i == 0)
        a[0] = "."
    for(var j = N-1; j >= 0; j--){
        if(j <= i){
            a.push("*");
        }else{
            a.push(" ");
        }
    }
    var b = [];
    if(i > 0)
        b = [a.join("").split(" ").join("").slice(1, a.length)];
    etg2.push(a.concat(b))
    arr.push(a.concat(b))
}

var str = "";
for(var i = 0; i < arr.length; i++){
    arr[i].forEach(v=>str+=v)
    str += "\n";
}
for(var i = 0; i < arr.length; i++){
    var s = "";
    etg2[i].forEach((v, j)=>{
        if(j >= N)
            s+=v;
    });
    str += s + (new Array(s.length - (i*2)).fill(" ").join("")) + s + "\n";
}

print(str.slice(0, str.length-1));
