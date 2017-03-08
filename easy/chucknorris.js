var MESSAGE = readline();
var PADDING = "0000000";
var c = "";
MESSAGE = MESSAGE.split('').reverse().join('');
for(var i = 0; i < MESSAGE.length; i++){
    var a = MESSAGE.charCodeAt(i);
    var b = "";
    var z;
    while( a > 0){
        if(a%2 === 0)
            b += "0";
        else
            b += "1";
            
        a = Math.floor(a / 2);
    }
    if(b.length < 7){
        z =  PADDING.substring(0, PADDING.length - b.length);
        c += b+z;    
    }else{
        c += b;
    }
}
c = c.split('').reverse().join('')
printErr(c)
var bin = "";
var resp = "";
var cpt = 0;
for(var i = 0; i < c.length; i++)
{   
    var temp = c[i];
    cpt++;
    if(temp === "0")
        bin = "00";
    else
        bin = "0";
    
    if(temp != c[i+1] || i == c.length-1){
        resp += bin + " ";
        for(var j = 0; j < cpt; j++)
            resp += "0";
        resp += " ";
        cpt = 0;
    }
}

print(resp.trim());