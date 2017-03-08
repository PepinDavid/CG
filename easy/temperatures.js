var n = parseInt(readline());
var temps = readline().split(' ').map(v=>parseInt(v));
var t1, t2;
if(temps[0]){
   t1 = temps[0]>>>0;
   t2 = -Math.abs(temps[0]);
    for(var i = 0; i < n; i++)
    {
        if(temps[i] >= 0 && t1 > temps[i])
            t1 = temps[i];
        if(temps[i] < 0 && t2 < temps[i])
            t2 = temps[i];
    }
    (t1 <= Math.abs(t2))? print(t1) : print(t2);
}else
    print(0);
