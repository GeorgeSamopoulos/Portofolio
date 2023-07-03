

function SignUp() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#container1').html((xhr.getResponseHeader("Message")));

        } else if (xhr.status !== 200) {
            console.log("Insertion failed");
        }
    };

    var data = $('#form').serialize();
    console.log(data);
    console.log(lat);
    console.log(lon);

    xhr.open('GET', 'SignUp?' + data + "&lat=" + lat + "&lon=" + lon);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();


}


function TestUser() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {

            SignUp();
        } else if (xhr.status !== 200) {
            alert(xhr.responseText);
        }
    };
    var data = $('#form').serialize();
    xhr.open('GET', 'TestUser?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();


}

//---------------------------------------------- LOGIN ----------------------------------------

function GetUser(flag) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log(xhr.responseText);
            var d = JSON.parse(xhr.responseText);
            if (d.username == "admin" && d.password == "admin12*") {
                LoginAdmin();
            } else {
                LoginUser(xhr.responseText);
            }

        } else if (xhr.status !== 200) {
            GetDoctor(data, flag);
            // alert("Wrong username or password");
        }
    };
    var data = $('#loginuser').serialize();
    console.log(data);
    var s = "&flag=" + flag;
    xhr.open('GET', 'GetUser?' + data + s);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

//--------------- DOCTOR -------------------------------
function GetDoctor(data, flag) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log(xhr.responseText);
            var d = JSON.parse(xhr.responseText);
            if (d.certified == 1) {

                LoginDoctor(d);
            } else {
                alert("You are not certified");
            }

        } else if (xhr.status !== 200) {
            //GetDoctor(data,s,true);
            alert("Wrong username or password");
        }
    };
    var s = "&flag=" + flag
    xhr.open('GET', 'GetDoctor?' + data + s);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function LoginDoctor(data) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            old = $('#container1').html();

            $('#container1').html(xhr.responseText);
            $('#container2').html(addCalendar());
            $('#logoutbutt').html("<br><input type=\"button\" value=\"Log Out\" onclick=\"LogOut();\">");

            //calendarSettings();
        } else if (xhr.status !== 200) {

        }
    };
    var param = data;
    var queryString = Object.keys(param).map(key => key + '=' + param[key]).join('&');
    xhr.open('GET', 'LoginDoctor?' + queryString);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function addCalendar() {

    var result = "<input type=\"text\" data-type=\"date\" id=\"date-input\" onchange=\"findRandevouz()\"/>\n" + "<br>";

    result += "<div id = \"radev\"></div>";
    result += "<div id= \"addradev\"></div>"
    result += "<div id= \"treat\"></div>"

    return result;
}

function treatForm() {
    var s = "<br><form id=\"addtreat\" >\n";
    s += "<label for=\"lastnameT\">* patient's lastname : </label>\n";
    s += "<input type=\"text\" id=\"lastnameT\" name=\"lastnameT\" required>\n"
    s += "<label for=\"firstnameT\">* patient's firstname : </label>\n";
    s += "<input type=\"text\" id=\"firstnameT\" name=\"firstnameT\" required>\n"
    s += "<label for=\"treatT\"> Treatment : </label>\n";
    s += "<textarea type=\"text\" id=\"treatT\" name=\"treatT\"></textarea>\n"

    s += "<label for=\"startT\">* start : </label>\n";
    s += "<input type=\"date\" id=\"startT\" name=\"startT\" required>\n"

    s += "<label for=\"endT\">* end : </label>\n";
    s += "<input type=\"date\" id=\"endT\" name=\"endT\" required>\n"

    s += "<label for=\"bloodId\">* blood test's id : </label>\n";
    s += "<input type=\"number\" id=\"bloodId\" name=\"bloodId\" min=1 required>\n"

    s += "<input type=\"button\" value=\"Add\" onclick=\"addTreatment();\">\n"
    s += "</form>";
    return s;

}

function addTreatment() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
//            $('#' + id).remove();
            alert("Treatment Add Succefully");
        } else if (xhr.status !== 200) {
            alert("Treatment Add Failed");
        }
    };
    var data = $('#addtreat').serialize();
    console.log(data);
    xhr.open('GET', 'AddTreatment?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function findRandevouz() {
    $('#radev').html("");
    $('#addradev').html("");
    $('#treat').html("");
    var result = "";
    var d = document.getElementById("date-input").value;
    var indate = d.split("/");
    var cy = new Date().getFullYear();
    var cm = new Date().getMonth();
    var cd = new Date().getDay();
    if (indate[2] == cy) {
        if (indate[1] == cm) {
            if (indate[0] < cd) {
                return;
            }
        } else if (indate[1] < cm) {
            return;
        }
    } else if (indate[2] < cy) {
        return;
    }
    var ts = indate[2] + "/" + indate[1] + "/" + indate[0] + " " + "7:59:00";
    var te = indate[2] + "/" + indate[1] + "/" + indate[0] + " " + "20:31:00";
    getRandevouz(ts, te);

}

function CancelRandevouz(id) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#' + id).remove();
            alert("Deleted Succefully");
        } else if (xhr.status !== 200) {
            alert("Delete Failed");
        }
    };
    xhr.open('GET', 'DeleteRandevouz?' + "&id=" + id);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function DoneRandevouz(id) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#' + id).remove();
            $('#container3').html("");
            $('#container3').html(xhr.responseText);
            $('#treat').html(treatForm());
            //$('#mez').html(selectMez(id));
            //CancelRandevouz(id);

            //alert("Done Succefully");
        } else if (xhr.status !== 200) {
            alert("Done Failed");
        }
    };
    xhr.open('GET', 'DoneRandevouz?' + "&id=" + id);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function GetGraph(uid) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log(xhr.responseText);
            var ar = xhr.responseText.split(" ");
            console.log(ar[0]);
            var dates = new Array();
            var mes = new Array();
            var i = 0;
            while (ar[i]) {
                var temp = ar[i].split(":");
                console.log(temp[0]);
                console.log(temp[1]);
                dates[i] = temp[0];
                mes[i] = temp[1];
                i++;
            }
            drawChart(data, mes, dates);
        } else if (xhr.status !== 200) {
            //alert("Update Failed Email");
        }
    };

    var data = document.querySelector('input[name="mez"]:checked').value;
    /*var i;
     var mez;
     for(i=0;i<data.legth;i++){
     if(data[i].checked){
     mez = data[i].value;
     }
     console.log(data[i].value);
     }*/
    console.log(data);
    xhr.open('GET', 'GetMeasure?' + "mez=" + data + "&id=" + uid);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function getRandevouz(ts, te) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#radev').html(xhr.responseText)
            var form = "<br><form id=\"addrad\" >\n";

            form += "<label for=\"lastnameR\">* patient's lastname : </label>\n";
            form += "<input type=\"text\" id=\"lastname\" name=\"lastnameR\" required>\n"

            form += "<label for=\"firstnameR\">* patient's firstname : </label>\n";
            form += "<input type=\"text\" id=\"firstname\" name=\"firstnameR\" required>\n"

            form += "<label for=\"priceR\">* price : </label>\n";
            form += "<input type=\"number\" id=\"price\" name=\"priceR\" min=10 max=80 required>\n"

            form += "<label for=\"doctor_infoR\"> doctor's info : </label>\n";
            form += "<textarea type=\"text\" id=\"doctor_info\" name=\"doctor_infoR\"></textarea>\n"

            form += "<label for=\"user_infoR\"> user's info : </label>\n";
            form += "<textarea type=\"text\" id=\"user_info\" name=\"user_infoR\"></textarea>\n"

            form += "<label for=\"timeR\">* time : </label>\n";
            form += "<input type=\"time\" id=\"time\" name=\"timeR\" min=\"12:00\" max=\"18:00\" step=\"00:30\" required>\n"


            form += "<input type=\"button\" value=\"Add\" onclick=\"addRandevDoc();\">\n"
            form += "</form>";
            $('#addradev').html(form);
        } else if (xhr.status !== 200) {
            alert("Empty");
        }
    };
    xhr.open('GET', 'getRandevouz?' + "&timestart=" + ts + "&timeend=" + te);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function sendAnswear(uid) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            //UpdateDataDoctor(data);
        } else if (xhr.status !== 200) {
            //alert("Update Failed Email");
        }
    };

    var data = document.getElementById("AnswearBox").value;
    console.log(data);
    console.log(uid);
    xhr.open('GET', 'SendMessageDoctor?' + "message=" + data + "&id=" + uid);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function addRandevDoc() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            alert("Add Randevouz successfully");
        } else if (xhr.status !== 200) {
            alert("Add Randevouz failed");
        }
    };

    var data = $('#addrad').serialize();
    var x = document.getElementById("time").value;
    var date = document.getElementById("date-input").value;
    var datear = date.split("/");
    date = datear[2] + "-" + datear[1] + "-" + datear[0];
    xhr.open('GET', 'AddRandevouz?' + data + "&time=" + x + "&date=" + date);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function TestDataDoctor() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            UpdateDataDoctor(data);
        } else if (xhr.status !== 200) {
            alert("Update Failed Email");
        }
    };

    var data = $('#UserData').serialize();
    xhr.open('GET', 'TestDataDoctor?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function UpdateDataDoctor(data) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            alert("Successful Update");
        } else if (xhr.status !== 200) {
            alert("Update Failed");
        }
    };
    xhr.open('GET', 'UpdateDataDoctor?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}
//--------------- ADMIN --------------------------------
function LoginAdmin() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            old = $('#container1').html();

            $('#container1').html(xhr.responseText);
        } else if (xhr.status !== 200) {

        }
    };

    xhr.open('GET', 'LoginAdmin?');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}


function VerifyDoctor(name) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            var el = document.getElementById(name);
            el.remove();
        } else if (xhr.status !== 200) {

        }
    };

    xhr.open('GET', 'VerifyDoctor?' + "&name=" + name);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function DeleteUser(name) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            var el = document.getElementById(name);
            el.remove();
        } else if (xhr.status !== 200) {

        }
    };
    /*var name1 = {username:name};
     var json = JSON.stringify(name1);*/
    xhr.open('GET', 'DeleteUser?' + "&name=" + name);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function DeleteDoctor(name) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            var el = document.getElementById(name);
            el.remove();
        } else if (xhr.status !== 200) {

        }
    };

    xhr.open('GET', 'DeleteDoctor?' + "&name=" + name);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

//------------------------ User ------------------------
var old;
var flag1 = false, flag2 = false, s1, s2;
function LoginUser(data) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
//        console.log(xhr);
        if (xhr.readyState == 4 && xhr.status == 200) {
            old = $('#container1').html();
//            var username = session.getAttribute("name");
//            var password = session.getAttribute("pass");
//            console.log(username);
//            console.log(password);
            var addTestForm = "<h3>Add new blood test</h3><br>\n";

            addTestForm += "<form id=\"addTest\">\n";
            addTestForm += "<label for=\"" + "dateTest" + "\">" + "date : " + "</label>\n";
            addTestForm += "<input type=\"date\" id=\"dateTest\" name = \"dateTest\">\n";

            addTestForm += "<label for=\"" + "medicalCenter" + "\">" + " medical center : " + "</label>\n";
            addTestForm += "<input type=\"text\" id=\"medicalCenter\" name = \"medicalCenter\">\n";

            addTestForm += "<label for=\"" + "bloodsugar" + "\">" + " blood sugar : " + "</label>\n";
            addTestForm += "<input type=\"number\" id=\"bloodsugar\" name = \"bloodsugar\">\n";

            addTestForm += "<label for=\"" + "cholesterol" + "\">" + " cholesterol : " + "</label>\n";
            addTestForm += "<input type=\"number\" id=\"cholesterol\" name = \"cholesterol\">\n";

            addTestForm += "<label for=\"" + "iron" + "\">" + " iron : " + "</label>\n";
            addTestForm += "<input type=\"number\" id=\"iron\" name = \"iron\">\n";

            addTestForm += "<label for=\"" + "vitamin_d3" + "\">" + " vitamin_d3 : " + "</label>\n";
            addTestForm += "<input type=\"number\" id=\"vitamin_d3\" name = \"vitamin_d3\">\n";

            addTestForm += "<label for=\"" + "vitamin_b12" + "\">" + " vitamin_b12 : " + "</label>\n";
            addTestForm += "<input type=\"number\" id=\"vitamin_b12\" name = \"vitamin_b12\">\n";

            addTestForm += "<input type=\"button\" id=\"addTestButton\" name = \"addTestButton\" value=\"Add Blood Test\" onclick=\"addBloodTest()\">\n";
            addTestForm += "</form><br>\n";
            addTestForm += "<div id=\"bloodtest\"></div>";
            addTestForm += "<input type=\"button\" id=\"watch_test_graph\" name = \"watch_test_graph\" value=\"Watch Blood Test Graph\" onclick=\"getBloodGraph()\">\n";
            addTestForm += "<input type=\"button\" id=\"watch_test_table\" name = \"watch_test_table\" value=\"Watch Blood Test Table\" onclick=\"getBloodTable()\"><br>\n";
            addTestForm += "<div id=\"bloodtestTable\"></div>";
            addTestForm += "<div id=\"bloodtestGraph\"></div>";
            addTestForm += "<br><label for=\"docSel\">Find Doctor by:</label>";

            addTestForm += "<input type=\"radio\" name=\"docSel\" value=\"car\" checked>Car";
            addTestForm += "<input type=\"radio\" name=\"docSel\" value=\"walk\">Walk";

            addTestForm += "<input type=\"button\" value=\"Get\" onclick=\"GetDoctors()\">";
            addTestForm += "<br><div id=\"doctorlist\"></div>";
            console.log(username);
            console.log(password);
            addTestForm += "<input type=\"button\" id=\"watchTreatments\" name = \"addTestButton\" value=\"Watch Treatments\" onclick=\"getTreatments()\">\n";


            $('#container2').html(addTestForm);
            getBloodTests();

            $('#logoutbutt').html("<br><input type=\"button\" value=\"Log Out\" onclick=\"LogOut();\">");
            var g;
            console.log(param["height"]);
            if (param["gender"] == "on") {
                g = "male";
            } else {
                g = "female";
            }
            GetBmi(parseFloat(param["weight"]), parseInt(param["height"]), DateConv(param["birthdate"]), g, xhr.responseText);


        } else if (xhr.status !== 200) {
            alert(xhr.responseText);

        }
    };
    var param = JSON.parse(data);
    var queryString = Object.keys(param).map(key => key + '=' + param[key]).join('&');
    xhr.open('GET', 'LoginUser?' + queryString);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function GetDoctors() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            var params = xhr.responseText.split("+");
            var origin = params[0].split("&")
            var lat = origin[0];
            var lon = origin[1];
            $('#doctorlist').html(xhr.responseText);
        } else if (xhr.status == 403) {
            var params = xhr.responseText.split("+");
            var origin = params[0].split("&")
            var lat = origin[0];
            var lon = origin[1];
            console.log(lat);
            console.log(lon);
            console.log(params[1]);
            ByCar(lat,lon,params[1]);
        } else if (xhr.status !== 200) {
            //alert("Update Failed Email");
        }
    };
    
    var data = document.querySelector('input[name="docSel"]:checked').value;
    xhr.open('GET', 'GetDoctorsUser?' + "by=" + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}


function ByCar(lat,lon,param) {

    const data = null;

    const xhr = new XMLHttpRequest();
    xhr.withCredentials = true;

    xhr.addEventListener("readystatechange", function () {
        if (this.readyState === this.DONE) {
            var values = JSON.parse(xhr.responseText);
            var d = values.durations[0];
            PrintByCar(d);
        }
    });
    console.log(param);
    xhr.open("GET", "https://trueway-matrix.p.rapidapi.com/CalculateDrivingMatrix?origins="+lat+"%2C"+lon+"&destinations="+param);
    xhr.setRequestHeader("x-rapidapi-host", "trueway-matrix.p.rapidapi.com");
    xhr.setRequestHeader("x-rapidapi-key", "b281dd5c52msh7edc8121a6df40fp102b99jsnb121b93d9748");

    xhr.send(data);
}


function PrintByCar(d){
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            
            $('#doctorlist').html(xhr.responseText);
        
        } else if (xhr.status !== 200) {
            //alert("Update Failed Email");
        }
    };
    var data = "";
    var i=0;
    for(i=0;i<d.length;i++){
        if(i!=0){
            data+="&";
        }
        data+="dis"+i+"="+d[i];
    }
    console.log(data);
    xhr.open('GET', 'GetDoctorByCar?'+data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
    
    
}

function SelectDoctor(did){
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {

        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#usermess').html(xhr.responseText);
        } else if (xhr.status !== 200) {
            console.log("Get bloodtestTable Failed");
        }
    };

    xhr.open('GET', 'getSuccessfulRand?id='+did);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
    
}


function sendMessageUser(did){
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            //UpdateDataDoctor(data);
        } else if (xhr.status !== 200) {
            //alert("Update Failed Email");
        }
    };

    var data = document.getElementById("AnswearBox").value;
    xhr.open('GET', 'SendMessageUser?' + "message=" + data + "&id=" + did);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function getBloodTable() {

    //console.log("ok table");
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {

        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#bloodtestGraph').html("");
            $('#bloodtestTable').html(xhr.responseText);
        } else if (xhr.status !== 200) {
            console.log("Get bloodtestTable Failed");
        }
    };

    xhr.open('GET', 'getBloodTestsData?flag=1');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}


function getBloodGraph() {


    //console.log("ok graph");
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {

        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#bloodtestTable').html("");
            $('#bloodtestGraph').html(xhr.responseText);
        } else if (xhr.status !== 200) {
            console.log("Get bloodtestGraph Failed");
        }
    };

    xhr.open('GET', 'getBloodTestsData?flag=0');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function GetGraphUser() {


    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log(xhr.responseText);
            var ar = xhr.responseText.split(" ");
            console.log(ar[0]);
            var dates = new Array();
            var mes = new Array();
            var i = 0;
            while (ar[i]) {
                var temp = ar[i].split(":");
                console.log(temp[0]);
                console.log(temp[1]);
                dates[i] = temp[0];
                mes[i] = temp[1];
                i++;
            }
            drawChart(data, mes, dates);
        } else if (xhr.status !== 200) {
            //alert("Update Failed Email");
        }
    };

    var data = document.querySelector('input[name="mez"]:checked').value;
    console.log(data);
    xhr.open('GET', 'GetMeasureUser?' + "mez=" + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function getTreatments() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {

        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#container3').html(xhr.responseText);
        } else if (xhr.status !== 200) {
            console.log("Get Treatments Failed");
        }
    };

    xhr.open('GET', 'getTreatments');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function getBloodTests() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {

        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#bloodtest').html(xhr.responseText);
        } else if (xhr.status !== 200) {
            console.log("Get Test Failed");
        }
    };

    xhr.open('GET', 'getBloodTests');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function addBloodTest() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {

        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log("Added Succefully");
        } else if (xhr.status !== 200) {
            console.log("Add Failed");
        }
    };
    var data = $("#addTest").serialize();
    xhr.open('GET', 'AddBloodTest?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}


function convertS(s1, s2) {
    var s = "";
    var obj = JSON.parse(s1);
    var d1 = obj.data.health;
    obj = JSON.parse(s2);
    var d2 = obj.data.Devine;

    s += "<p> The ideal weight for you is : " + d2 + "<br>Health condition : " + d1 + "</p>";
    return s;
}

function DateConv(date) {
    var s = date[0] + date[1] + date[2] + date[3];
    var y = parseInt(s);
    return (2021 - y);
}

//-------------------API's start----------------

function GetBmi(w, h, y, g, s) {
    const data = null;

    const xhr = new XMLHttpRequest();
    xhr.withCredentials = true;

    xhr.addEventListener("readystatechange", function () {
        if (this.readyState == this.DONE) {

            console.log((this.responseText));
            s1 = this.response;
            GetIdeal(h, g, s);

        }

    });

    xhr.open("GET", "https://fitness-calculator.p.rapidapi.com/bmi?age=" + y + "&weight=" + w + "&height=" + h);
    xhr.setRequestHeader("x-rapidapi-host", "fitness-calculator.p.rapidapi.com");
    xhr.setRequestHeader("x-rapidapi-key", "9fc5c7c19emsh2960f3d003a1c14p1fcc11jsn930cd99f1b26");

    xhr.send(data);

}

function GetIdeal(h, g, s) {
    const data = null;

    const xhr = new XMLHttpRequest();
    xhr.withCredentials = true;

    xhr.addEventListener("readystatechange", function () {
        if (this.readyState == this.DONE) {
            console.log((this.responseText));
            while (s2 == null)
                s2 = this.responseText;
            $('#container1').html(s + convertS(s1, s2));
        }

    });

    xhr.open("GET", "https://fitness-calculator.p.rapidapi.com/idealweight?gender=" + g + "&height=" + h);
    xhr.setRequestHeader("x-rapidapi-host", "fitness-calculator.p.rapidapi.com");
    xhr.setRequestHeader("x-rapidapi-key", "9fc5c7c19emsh2960f3d003a1c14p1fcc11jsn930cd99f1b26");

    xhr.send(data);
}



//-------------------API's end------------------
function TestData() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            UpdateData(data);
        } else if (xhr.status !== 200) {
            alert("Update Failed Email");
        }
    };

    var data = $('#UserData').serialize();
    xhr.open('GET', 'TestData?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();
}

function UpdateData(data) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            alert("Successful Update");
        } else if (xhr.status !== 200) {
            alert("Update Failed");
        }
    };
    xhr.open('GET', 'UpdateData?' + data);
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

function LogOut() {

    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            $('#container1').html(old);
            $('#container2').html("");
            $('#container3').html("");
            $('#mez').html("");
            $('#viz').html("");
            $('#logoutbutt').html("");
            console.log(xhr.responseText);
        } else if (xhr.status !== 200) {
            alert("LogOut Failed");
        }
    };
    xhr.open('GET', 'LogOut');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send();

}

//========================================== Charts ================================================
google.charts.load("current", {packages: ["corechart"]});
google.charts.setOnLoadCallback(drawChart);
function drawChart(mez, mes, dates) {
    var data = google.visualization.arrayToDataTable([
        ["Element", "Density", {role: "style"}],
        [dates[0], parseFloat(mes[0]), "blue"],
        [dates[1], parseFloat(mes[1]), "blue"],
        [dates[2], parseFloat(mes[2]), "blue"],
        [dates[3], parseFloat(mes[3]), "blue"]
    ]);

    var view = new google.visualization.DataView(data);
    view.setColumns([0, 1,
        {calc: "stringify",
            sourceColumn: 1,
            type: "string",
            role: "annotation"},
        2]);

    var options = {
        title: mez,
        width: 600,
        height: 400,
        bar: {groupWidth: "95%"},
        legend: {position: "none"},
    };
    var chart = new google.visualization.BarChart(document.getElementById("viz"));
    chart.draw(view, options);
}