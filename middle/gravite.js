/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var inputs = readline().split(' ');
var width = parseInt(inputs[0]);
var height = parseInt(inputs[1]);
var arr = [];
for (var i = 0; i < height; i++) {
    var line = readline();
    arr.push(line);
}

var arrF = new Array(arr[0].length);

for(var i = 0; i < arrF.length; i++){
    arrF[i] = new Array(arr.length);
}

for(var i = 0; i < arr.length; i++){
    var str = arr[i];
    for(var j = 0; j < str.length; j++){
        var c = str[j];
        arrF[j][i] = c;
    }
}

var arrFinal = new Array(arr.length);
for(var i = 0; i < arrFinal.length; i++){
    arrFinal[i] = new Array(arr[0].length)
}
for(var i = 0; i < arrF.length; i++){
    arrF[i].sort((a,b)=>{return a < b});
    var str = arrF[i];
    for(var j = 0; j < str.length; j++){
        var c = str[j];
        arrFinal[j][i] = c;
    }
}

arrFinal.forEach(v=>print(v.join('')));
