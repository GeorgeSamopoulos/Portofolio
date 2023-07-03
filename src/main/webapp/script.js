/* 
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/JavaScript.js to edit this template
 */


function ComparePass(){
    var pass1 = document.getElementById('repassword').value;
    var pass2 = document.getElementById('password').value;
    if(pass1!=pass2){
        document.getElementById('repeatpass').textContent="(password not equal)";
    }else{
        document.getElementById('repeatpass').textContent="";
    }
}

function ViewPassp(){

    var pa = document.getElementById('password');
    if(pa.type=='text'){
        pa.type='password';
    }else{
        pa.type='text';
    }
}

function ViewPassr(){

    var pa = document.getElementById('repassword');
    if(pa.type=='text'){
        pa.type='password';
    }else{
        pa.type='text';
    }
}


function CompareAMKA(){
    var amkav=document.getElementById("amka").value;
    if(amkav.toString().length==11){
        var birthv=document.getElementById("birthday").value;
        var comp = birthv[8]+birthv[9]+birthv[5]+birthv[6]+birthv[2]+birthv[3];
        var amkanew=amkav[0]+amkav[1]+amkav[2]+amkav[3]+amkav[4]+amkav[5];
        if(comp!=amkanew){
            document.getElementById("amka").value='';
            alert("AMKA does not match with birthday date");
        }
    }
}


function testcheckbox(){
    var check=document.getElementById("agree").checked;
    if(check==false){
        alert("You have to agree with terms");
    }
}

var flag;
var newselect;
var textdoc;
var nl1;
var nl2;
var nl3;
function usertypeadd(){
    var parentel = document.getElementById("usertype");
    
    if(parentel.value=="Doctor"){
        flag = true;
        
        
        /*add select bar*/
        newselect=document.createElement("SELECT");
        newselect.setAttribute("id","doctorspec");
        parentel.parentNode.insertBefore(newselect,parentel.nextSibling);
        var option1=document.createElement("option");
        option1.value = "pathologist" ;
        option1.text = "pathologist"
        newselect.add(option1);
        var option2 = document.createElement("option");
        option2.value = "general doctor" ;
        option2.text = "general doctor" ;
        newselect.add(option2);
        
        /*change address label*/
        
        var name = document.getElementById("addname");
        name.innerText="* Doctor's Address Name : ";
        var code = document.getElementById("addcode");
        code.innerText="* Doctor's address Code : ";
        var number = document.getElementById("addnumber");
        number.innerText="* Doctor's address Number : ";
        
        
        /*add new line*/
        nl2 = document.createElement("br");
        parentel.parentNode.insertBefore(nl2,parentel.nextSibling);
        
        /*add textarea*/
        
        textdoc=document.createElement("textarea");
        textdoc.value="Doctor's info";
        textdoc.setAttribute("id","doctortext");
        parentel.parentNode.insertBefore(textdoc,parentel.nextSibling);
        
        /*add new line*/
        nl1 = document.createElement("br");
        parentel.parentNode.insertBefore(nl1,parentel.nextSibling);
        nl3 = document.createElement("br");
        parentel.parentNode.insertBefore(nl3,parentel.nextSibling);
        
    }else{
        
        if(flag==true){
            document.getElementById("form").removeChild(newselect);
            document.getElementById("form").removeChild(textdoc);
            document.getElementById("form").removeChild(nl1);
            document.getElementById("form").removeChild(nl2);
            document.getElementById("form").removeChild(nl3);

        }
        flag = false;
        /*change address label*/
        var name = document.getElementById("addname");
        name.innerText="* Address Name : ";
        var code = document.getElementById("addcode");
        code.innerText="* Address Code : ";
        var number = document.getElementById("addnumber");
        number.innerText="* Address Number : ";
    }
}


function testpassword(){
    var pass=document.getElementById("password").value;
    var i;
    var len=pass.length;
    var num=0;
    var elemArr = [];
    var countArr = [];
    for(i=0;i<len;i++){
        var a=pass.charAt(i);
        if(isNaN(a)!=true){
            num++;
        }

        var flag=false;
        var j;
        for(j=0;j<elemArr.length;j++){
            if(elemArr[j]==a){
                flag=true;
                countArr[j]++;
                break;
            }
        }
        if(flag==false){
            elemArr.push(a);
            countArr.push(1);
        }
    }
    var test=false;
    var test1=false;
    for(i=0;i<countArr.length;i++){
        if(countArr[i]>=(len/2)){
            test=true;
            break;
        }
    }
    if(len!=0){
        if((elemArr.length/len)>=0.8){
            test1=true; 
        }
    }
    if(num>=(len/2)){
        document.getElementById("strength").innerHTML="WEAK";
        return;
    }else if(test==true){
        document.getElementById("strength").innerHTML="WEAK";
        return;
    }else if(test1==true){
        document.getElementById("strength").innerHTML="STRONG";
        return;
    }
    document.getElementById("strength").innerHTML="MEDIUM";
}

var mapf=false;
var lat,lon;

function Api(fl){
    const data = null;

    const xhr = new XMLHttpRequest();
    xhr.withCredentials = true;

    xhr.addEventListener("readystatechange", function () {
        if (this.readyState === this.DONE) {
            var obj=JSON.parse(this.responseText);
            console.log(obj);
            if(fl==true){
                testobj(obj);}else{
                    lat=parseFloat(obj[0].lat);
                    lon=parseFloat(obj[0].lon);
                    TestUser();
            }
        }
        
    });
    var addrname=document.getElementById("addressname").value;
    var addrnumber=document.getElementById("addressnumber").value;
    var city=document.getElementById("city").value;
    var country=document.getElementById("country").value;
    var input=addrname+" "+addrnumber+" "+city+" "+country;

    xhr.open("GET", "https://forward-reverse-geocoding.p.rapidapi.com/v1/search?q="+input+"&acceptlanguage=en&polygon_threshold=0.0");
    xhr.setRequestHeader("x-rapidapi-host", "forward-reverse-geocoding.p.rapidapi.com");
    xhr.setRequestHeader("x-rapidapi-key", "9fc5c7c19emsh2960f3d003a1c14p1fcc11jsn930cd99f1b26");

    xhr.send(data);
}


function testobj(obj){
    if(obj[0]==undefined){
        document.getElementById("locationerror").innerHTML="Location does not exist";
        return;
    }
    document.getElementById("locationerror").innerHTML="";
    lat=parseFloat(obj[0].lat);
    lon=parseFloat(obj[0].lon);
    var words=(obj[0].display_name).split(", ");
    var flag=false;
    for(var i=0;i<words.length;i++){
        if(words[i]=="Region of Crete"){
            flag=true;
        }
    }
    
    if(flag==false){
        document.getElementById("locationerror").innerHTML="Region is out of Crete";
        return;
    }
    removeMap();
    createMap();
}

function createMap(){
    var addrname=document.getElementById("addressname").value;
    var addrnumber=document.getElementById("addressnumber").value;
    var city=document.getElementById("city").value;
    var par = document.getElementById("mn");
    var ch = document.createElement("div");
    ch.id="Map";
    console.log(ch);
    par.insertAdjacentElement("afterend",ch);
    map = new OpenLayers.Map("Map");
    var mapnik = new OpenLayers.Layer.OSM();
    map.addLayer(mapnik);
    mapf=true;
    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);
    var position=setPosition(lon, lat);
    var mar=new OpenLayers.Marker(position);
    markers.addMarker(mar);
    mar.events.register('mousedown', mar, function(evt){
            handler(position,(addrname+" "+addrnumber+","+city));
    });
    const zoom = 13;
    map.setCenter(position, zoom);

}

function showDocMap(){
    var flag=document.getElementById("docButton").value;
    if(flag=="true"){
        document.getElementById("map_container").innerHTML="";
        document.getElementById("docButton").value="false";
    }else{
        createMap();
        document.getElementById("docButton").value="true";
    }
    
}   

function createMap(){

    var map = new OpenLayers.Map("map_container");
    var mapnik = new OpenLayers.Layer.OSM();
    map.addLayer(mapnik);
    document.getElementById("map_container").style.display = "block";
    var lat = 25.1442
    var lon = 35.3387

    //Markers
    var markers = new OpenLayers.Layer.Markers("Markers");
    map.addLayer(markers);

    //Protos Marker
    var position = setPosition(lat, lon);
    var mar = new OpenLayers.Marker(position);
    markers.addMarker(mar);
   

    //Orismos zoom
    const zoom = 12;
    map.setCenter(position, zoom);
}

function setPosition(lon, lat){
    var fromProjection = new OpenLayers.Projection("EPSG:4326"); 
    var toProjection = new OpenLayers.Projection("EPSG:900913"); 
    var position = new OpenLayers.LonLat(lon, lat).transform( fromProjection,
    toProjection);
    return position;
}

function handler(position, message){
    var popup = new OpenLayers.Popup.FramedCloud("Popup",position, null,message, null,true );
    map.addPopup(popup);
}

function removeMap(){
    if(mapf==true){
        document.getElementById("Map").remove();
    }
}


//---------------------

var findloc;
function findlocation(){
    getLocation();
    
    if(findloc.address.city!=undefined){
        document.getElementById("city").value=findloc.address.city;
    }else{
        document.getElementById("city").insertAdjacentText("afterend", "(city not found)");
    }

    if(findloc.address.country!=undefined){
        document.getElementById("country").value=findloc.address.country;
    }else{
        document.getElementById("country").insertAdjacentText("afterend", "(city not found)");
    }

    if(findloc.address.road!=undefined){
        document.getElementById("addressname").value=findloc.address.road;
    }else{
        document.getElementById("addressname").insertAdjacentText("afterend", "(address name not found)");
    }

    if(findloc.address.postcode!=undefined){
        document.getElementById("addresscode").value=findloc.address.postcode;
    }else{
        document.getElementById("addresscode").insertAdjacentText("afterend", "(postcode not found)");
    }

    if(findloc.address.addressnumber!=undefined){
        document.getElementById("addressnumber").value=findloc.address.addressnumber;
    }else{
        document.getElementById("addressnumber").insertAdjacentText("afterend", "(address number not found)");
    }
    
}

function getLocation() {
    if (navigator.geolocation) {
      navigator.geolocation.getCurrentPosition(searchLocation);
    } else {
      return;
    }
}

function searchLocation(pos){
    const data = null;
    lon=pos.coords.longitude;
    lat=pos.coords.latitude;
    const xhr = new XMLHttpRequest();
    xhr.withCredentials = true;
    
    xhr.addEventListener("readystatechange", function () {
        if (this.readyState === this.DONE) {
            findloc=JSON.parse(this.responseText);
        }
    });
    
    xhr.open("GET", "https://forward-reverse-geocoding.p.rapidapi.com/v1/reverse?lat="+lat+"&lon="+lon+"&accept-language=en&polygon_threshold=0.0");
    xhr.setRequestHeader("x-rapidapi-host", "forward-reverse-geocoding.p.rapidapi.com");
    xhr.setRequestHeader("x-rapidapi-key", "9fc5c7c19emsh2960f3d003a1c14p1fcc11jsn930cd99f1b26");
    
    xhr.send(data);


}