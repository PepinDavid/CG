var LON = parseFloat(readline().replace(',','.'));//float 
var LAT = parseFloat(readline().replace(',','.'));//float
printErr(LON+ " "+LAT);
var N = parseInt(readline());
var DEFIBs = [];
var searchArray = [];
var minLon = 10000, minLat = 10000;
for (var i = 0; i < N; i++) {
    var diffLat = 0;
    var diffLon = 0;
    var cpt = 0;
    var DEFIB = readline();
    while(cpt < 4)
    {
        var index = DEFIB.lastIndexOf(';');
        if(cpt === 0)
        {
            var index = DEFIB.lastIndexOf(';');
            lat = parseFloat(DEFIB.substr(index+1, DEFIB.length).replace(',','.'));
            DEFIB = DEFIB.substr(0,index);
            DEFIB.split(0,index);
        }                
        else if(cpt === 1)
        {
            var index = DEFIB.lastIndexOf(';');
            lon = parseFloat(DEFIB.substr(index+1, DEFIB.length).replace(',','.'));
            DEFIB = DEFIB.substr(0,index-1);
            DEFIB.split(0,index);
        }
        else if(cpt === 2)
        {
            var index = DEFIB.indexOf(';');
            DEFIB = DEFIB.substr(index+1, DEFIB.length);
        }
        else
        {
            var index = DEFIB.indexOf(';');
            DEFIB = DEFIB.substr(0,index);
            DEFIBs.push(DEFIB);
        }          
        cpt++;
    }
    var diff = Math.sqrt((LON-lon)*(LON-lon) + (LAT-lat)*(LAT-lat));
    printErr(diff)
    if(minLon >= diff)
    {
        minLon = diff;
        var dd = minLon;
        
        searchArray.push({key: i,distance: dd});
    }
}
var index = 0;
for(var d = 0; d < searchArray.length; d++)
{ 
    var o = searchArray[d];
    printErr(o.distance);
    if(minLon == o.distance)
    {
        minLon = o.distance;
        index = o.key;
    }                
}
print(DEFIBs[index]);