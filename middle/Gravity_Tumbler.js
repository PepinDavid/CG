/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var inputs = readline().split(' ');
var width = parseInt(inputs[0]);
var height = parseInt(inputs[1]);
var count = parseInt(readline());
const arr = [];

if (count % 2 !== 0) {
    for(var i = 0; i < width; i++){
        arr.push([]);
    }
} else {
    for(var i = 0; i < height; i++){
        arr.push([]);
    }
}

for (let i = 0; i < height; i++) {
    const raster = readline().split("").sort((a,b)=>{return a < b}).join("");

    if (count % 2 !== 0) {
        for(var j = 0; j < raster.length; j++){
            arr[j][i]  = raster[j];
        }
    } else {
        arr[i].push(raster)
    }
}

for (let i = 0; i < arr.length; i++) {
    print(arr[i].join(""))
}

