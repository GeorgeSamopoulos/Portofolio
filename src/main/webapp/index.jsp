<%-- 
    Document   : newjsp
    Created on : Dec 15, 2021, 2:25:42 PM
    Author     : GS
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" type="text/css" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.2/themes/smoothness/jquery-ui.css" media="screen"/>
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
        <link rel="stylesheet" type="text/css" href="calendar.css"/>
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jqueryui/1.12.0/jquery-ui.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.15.2/moment.js"></script>
        <link rel="stylesheet" href="styles.css">
        <script src="script.js"></script>
        <script src="ajax.js"></script>

        <script src="http://www.openlayers.org/api/OpenLayers.js"></script>


        <title>Hospital Login</title>
    </head>


    <body>
        <%
            if (session.getAttribute("name") != null) {
        %><script type="text/javascript">
            GetUser(false);
        </script><%
            }
        %>
        <div id="container1">

            <div id="mn">
                <h1 id="welcome">
                    WELCOME TO THE HOSPITAL
                </h1>
                <br>
                <div class="container">
                    <div class="row">
                        <div id="elements" class="col-sm-6">
                            <h3 id="signuphead">Sign Up</h3><br>
                            <form id="form" >
                                <label for="username" >* Username : </label>
                                <input type="text" id="username" name="username" pattern="[a-zA-Z0-9!@#$%^&*()].{8,}" title="Must have 8+ characters" required><br><br>

                                <label for="email" >* Email : </label>
                                <input type="email" id="email" name="email" pattern="[a-z0-9]+@+[a-z0-9]+\.+[a-z]{2,}" title="Must be legal" required><br><br>

                                <label for="password">* Password : </label>
                                <input type="password" id="password" name="password" pattern="(?=.*\d)(?=.*[a-zA-Z])(?=.*[!@#$%^&*()]).{8,15}" title="Must have 8-15 characters with min a character , a number and a symbol" required>
                                <input id="paButton" type="button" value="view" onclick="ViewPassp()">
                                <input id="strButton" type="button" value="see strength" onclick="testpassword()">
                                <span id="strength"></span>
                                <br><br>

                                <label for="repassword">* Repeat Password : </label>
                                <input type="password" id="repassword" name="repassword" oninput="ComparePass()" pattern="(?=.*\d)(?=.*[a-zA-Z])(?=.*[!@#$%^&*()]).{8,15}" title="Must have 8-15 characters with min a character , a number and a symbol" required>
                                <input id="reButton" type="button" value="view" onclick="ViewPassr()"> <span id="repeatpass"></span> <br><br>

                                <label for="usertype">* User Type : </label>
                                <select id="usertype" name="usertype" oninput="usertypeadd()" required>
                                    <option value="">Choose</option>
                                    <option value="default" selected>Default</option>
                                    <option value="Doctor">Doctor</option>
                                </select> <br><br>

                                <label for="firstname" >* First Name : </label>
                                <input type="text" id="firstname" name="first name" pattern=".{3,30}" title="Must have 3-30 characters" required><br><br>

                                <label for="lastname" >* Last Name : </label>
                                <input type="text" id="lastname" name="last name" pattern=".{3,30}" title="Must have 3-30 characters" required><br><br>

                                <label for="birthday" >* Birth Day : </label>
                                <input type="date" id="birthday" name="birthday"  min="1920-01-01" max="2005-12-31" title="Wrong Date" required><br>

                                <p>* Sex : </p>
                                <input type="radio" id="sex1" name="sex" required>
                                <label for="sex1">Male</label>
                                <input type="radio" id="sex2" name="sex" required>
                                <label for="sex2">Female</label>
                                <input type="radio" id="sex3" name="sex" required>
                                <label for="sex3">Other</label> <br><br>

                                <label for="amka" >* AMKA : </label>
                                <input type="text" id="amka" name="amka" oninput="CompareAMKA()" pattern="[0-9]{11}" title="Integer with 11 numbers" required><br><br>

                                <label for="country" >* Select a country : </label>
                                <select id="country"  onchange="removeMap()" name="country" required>
                                    <option value="">Choose</option>
                                    <option value="Afganistan">Afghanistan</option>
                                    <option value="Albania">Albania</option>
                                    <option value="Algeria">Algeria</option>
                                    <option value="American Samoa">American Samoa</option>
                                    <option value="Andorra">Andorra</option>
                                    <option value="Angola">Angola</option>
                                    <option value="Anguilla">Anguilla</option>
                                    <option value="Antigua & Barbuda">Antigua & Barbuda</option>
                                    <option value="Argentina">Argentina</option>
                                    <option value="Armenia">Armenia</option>
                                    <option value="Aruba">Aruba</option>
                                    <option value="Australia">Australia</option>
                                    <option value="Austria">Austria</option>
                                    <option value="Azerbaijan">Azerbaijan</option>
                                    <option value="Bahamas">Bahamas</option>
                                    <option value="Bahrain">Bahrain</option>
                                    <option value="Bangladesh">Bangladesh</option>
                                    <option value="Barbados">Barbados</option>
                                    <option value="Belarus">Belarus</option>
                                    <option value="Belgium">Belgium</option>
                                    <option value="Belize">Belize</option>
                                    <option value="Benin">Benin</option>
                                    <option value="Bermuda">Bermuda</option>
                                    <option value="Bhutan">Bhutan</option>
                                    <option value="Bolivia">Bolivia</option>
                                    <option value="Bonaire">Bonaire</option>
                                    <option value="Bosnia & Herzegovina">Bosnia & Herzegovina</option>
                                    <option value="Botswana">Botswana</option>
                                    <option value="Brazil">Brazil</option>
                                    <option value="British Indian Ocean Ter">British Indian Ocean Ter</option>
                                    <option value="Brunei">Brunei</option>
                                    <option value="Bulgaria">Bulgaria</option>
                                    <option value="Burkina Faso">Burkina Faso</option>
                                    <option value="Burundi">Burundi</option>
                                    <option value="Cambodia">Cambodia</option>
                                    <option value="Cameroon">Cameroon</option>
                                    <option value="Canada">Canada</option>
                                    <option value="Canary Islands">Canary Islands</option>
                                    <option value="Cape Verde">Cape Verde</option>
                                    <option value="Cayman Islands">Cayman Islands</option>
                                    <option value="Central African Republic">Central African Republic</option>
                                    <option value="Chad">Chad</option>
                                    <option value="Channel Islands">Channel Islands</option>
                                    <option value="Chile">Chile</option>
                                    <option value="China">China</option>
                                    <option value="Christmas Island">Christmas Island</option>
                                    <option value="Cocos Island">Cocos Island</option>
                                    <option value="Colombia">Colombia</option>
                                    <option value="Comoros">Comoros</option>
                                    <option value="Congo">Congo</option>
                                    <option value="Cook Islands">Cook Islands</option>
                                    <option value="Costa Rica">Costa Rica</option>
                                    <option value="Cote DIvoire">Cote DIvoire</option>
                                    <option value="Croatia">Croatia</option>
                                    <option value="Cuba">Cuba</option>
                                    <option value="Curaco">Curacao</option>
                                    <option value="Cyprus">Cyprus</option>
                                    <option value="Czech Republic">Czech Republic</option>
                                    <option value="Denmark">Denmark</option>
                                    <option value="Djibouti">Djibouti</option>
                                    <option value="Dominica">Dominica</option>
                                    <option value="Dominican Republic">Dominican Republic</option>
                                    <option value="East Timor">East Timor</option>
                                    <option value="Ecuador">Ecuador</option>
                                    <option value="Egypt">Egypt</option>
                                    <option value="El Salvador">El Salvador</option>
                                    <option value="Equatorial Guinea">Equatorial Guinea</option>
                                    <option value="Eritrea">Eritrea</option>
                                    <option value="Estonia">Estonia</option>
                                    <option value="Ethiopia">Ethiopia</option>
                                    <option value="Falkland Islands">Falkland Islands</option>
                                    <option value="Faroe Islands">Faroe Islands</option>
                                    <option value="Fiji">Fiji</option>
                                    <option value="Finland">Finland</option>
                                    <option value="France">France</option>
                                    <option value="French Guiana">French Guiana</option>
                                    <option value="French Polynesia">French Polynesia</option>
                                    <option value="French Southern Ter">French Southern Ter</option>
                                    <option value="Gabon">Gabon</option>
                                    <option value="Gambia">Gambia</option>
                                    <option value="Georgia">Georgia</option>
                                    <option value="Germany">Germany</option>
                                    <option value="Ghana">Ghana</option>
                                    <option value="Gibraltar">Gibraltar</option>
                                    <option value="Great Britain">Great Britain</option>
                                    <option value="Greece" selected>Greece</option>
                                    <option value="Greenland">Greenland</option>
                                    <option value="Grenada">Grenada</option>
                                    <option value="Guadeloupe">Guadeloupe</option>
                                    <option value="Guam">Guam</option>
                                    <option value="Guatemala">Guatemala</option>
                                    <option value="Guinea">Guinea</option>
                                    <option value="Guyana">Guyana</option>
                                    <option value="Haiti">Haiti</option>
                                    <option value="Hawaii">Hawaii</option>
                                    <option value="Honduras">Honduras</option>
                                    <option value="Hong Kong">Hong Kong</option>
                                    <option value="Hungary">Hungary</option>
                                    <option value="Iceland">Iceland</option>
                                    <option value="Indonesia">Indonesia</option>
                                    <option value="India">India</option>
                                    <option value="Iran">Iran</option>
                                    <option value="Iraq">Iraq</option>
                                    <option value="Ireland">Ireland</option>
                                    <option value="Isle of Man">Isle of Man</option>
                                    <option value="Israel">Israel</option>
                                    <option value="Italy">Italy</option>
                                    <option value="Jamaica">Jamaica</option>
                                    <option value="Japan">Japan</option>
                                    <option value="Jordan">Jordan</option>
                                    <option value="Kazakhstan">Kazakhstan</option>
                                    <option value="Kenya">Kenya</option>
                                    <option value="Kiribati">Kiribati</option>
                                    <option value="Korea North">Korea North</option>
                                    <option value="Korea Sout">Korea South</option>
                                    <option value="Kuwait">Kuwait</option>
                                    <option value="Kyrgyzstan">Kyrgyzstan</option>
                                    <option value="Laos">Laos</option>
                                    <option value="Latvia">Latvia</option>
                                    <option value="Lebanon">Lebanon</option>
                                    <option value="Lesotho">Lesotho</option>
                                    <option value="Liberia">Liberia</option>
                                    <option value="Libya">Libya</option>
                                    <option value="Liechtenstein">Liechtenstein</option>
                                    <option value="Lithuania">Lithuania</option>
                                    <option value="Luxembourg">Luxembourg</option>
                                    <option value="Macau">Macau</option>
                                    <option value="Macedonia">Macedonia</option>
                                    <option value="Madagascar">Madagascar</option>
                                    <option value="Malaysia">Malaysia</option>
                                    <option value="Malawi">Malawi</option>
                                    <option value="Maldives">Maldives</option>
                                    <option value="Mali">Mali</option>
                                    <option value="Malta">Malta</option>
                                    <option value="Marshall Islands">Marshall Islands</option>
                                    <option value="Martinique">Martinique</option>
                                    <option value="Mauritania">Mauritania</option>
                                    <option value="Mauritius">Mauritius</option>
                                    <option value="Mayotte">Mayotte</option>
                                    <option value="Mexico">Mexico</option>
                                    <option value="Midway Islands">Midway Islands</option>
                                    <option value="Moldova">Moldova</option>
                                    <option value="Monaco">Monaco</option>
                                    <option value="Mongolia">Mongolia</option>
                                    <option value="Montserrat">Montserrat</option>
                                    <option value="Morocco">Morocco</option>
                                    <option value="Mozambique">Mozambique</option>
                                    <option value="Myanmar">Myanmar</option>
                                    <option value="Nambia">Nambia</option>
                                    <option value="Nauru">Nauru</option>
                                    <option value="Nepal">Nepal</option>
                                    <option value="Netherland Antilles">Netherland Antilles</option>
                                    <option value="Netherlands">Netherlands (Holland, Europe)</option>
                                    <option value="Nevis">Nevis</option>
                                    <option value="New Caledonia">New Caledonia</option>
                                    <option value="New Zealand">New Zealand</option>
                                    <option value="Nicaragua">Nicaragua</option>
                                    <option value="Niger">Niger</option>
                                    <option value="Nigeria">Nigeria</option>
                                    <option value="Niue">Niue</option>
                                    <option value="Norfolk Island">Norfolk Island</option>
                                    <option value="Norway">Norway</option>
                                    <option value="Oman">Oman</option>
                                    <option value="Pakistan">Pakistan</option>
                                    <option value="Palau Island">Palau Island</option>
                                    <option value="Palestine">Palestine</option>
                                    <option value="Panama">Panama</option>
                                    <option value="Papua New Guinea">Papua New Guinea</option>
                                    <option value="Paraguay">Paraguay</option>
                                    <option value="Peru">Peru</option>
                                    <option value="Phillipines">Philippines</option>
                                    <option value="Pitcairn Island">Pitcairn Island</option>
                                    <option value="Poland">Poland</option>
                                    <option value="Portugal">Portugal</option>
                                    <option value="Puerto Rico">Puerto Rico</option>
                                    <option value="Qatar">Qatar</option>
                                    <option value="Republic of Montenegro">Republic of Montenegro</option>
                                    <option value="Republic of Serbia">Republic of Serbia</option>
                                    <option value="Reunion">Reunion</option>
                                    <option value="Romania">Romania</option>
                                    <option value="Russia">Russia</option>
                                    <option value="Rwanda">Rwanda</option>
                                    <option value="St Barthelemy">St Barthelemy</option>
                                    <option value="St Eustatius">St Eustatius</option>
                                    <option value="St Helena">St Helena</option>
                                    <option value="St Kitts-Nevis">St Kitts-Nevis</option>
                                    <option value="St Lucia">St Lucia</option>
                                    <option value="St Maarten">St Maarten</option>
                                    <option value="St Pierre & Miquelon">St Pierre & Miquelon</option>
                                    <option value="St Vincent & Grenadines">St Vincent & Grenadines</option>
                                    <option value="Saipan">Saipan</option>
                                    <option value="Samoa">Samoa</option>
                                    <option value="Samoa American">Samoa American</option>
                                    <option value="San Marino">San Marino</option>
                                    <option value="Sao Tome & Principe">Sao Tome & Principe</option>
                                    <option value="Saudi Arabia">Saudi Arabia</option>
                                    <option value="Senegal">Senegal</option>
                                    <option value="Seychelles">Seychelles</option>
                                    <option value="Sierra Leone">Sierra Leone</option>
                                    <option value="Singapore">Singapore</option>
                                    <option value="Slovakia">Slovakia</option>
                                    <option value="Slovenia">Slovenia</option>
                                    <option value="Solomon Islands">Solomon Islands</option>
                                    <option value="Somalia">Somalia</option>
                                    <option value="South Africa">South Africa</option>
                                    <option value="Spain">Spain</option>
                                    <option value="Sri Lanka">Sri Lanka</option>
                                    <option value="Sudan">Sudan</option>
                                    <option value="Suriname">Suriname</option>
                                    <option value="Swaziland">Swaziland</option>
                                    <option value="Sweden">Sweden</option>
                                    <option value="Switzerland">Switzerland</option>
                                    <option value="Syria">Syria</option>
                                    <option value="Tahiti">Tahiti</option>
                                    <option value="Taiwan">Taiwan</option>
                                    <option value="Tajikistan">Tajikistan</option>
                                    <option value="Tanzania">Tanzania</option>
                                    <option value="Thailand">Thailand</option>
                                    <option value="Togo">Togo</option>
                                    <option value="Tokelau">Tokelau</option>
                                    <option value="Tonga">Tonga</option>
                                    <option value="Trinidad & Tobago">Trinidad & Tobago</option>
                                    <option value="Tunisia">Tunisia</option>
                                    <option value="Turkey">Turkey</option>
                                    <option value="Turkmenistan">Turkmenistan</option>
                                    <option value="Turks & Caicos Is">Turks & Caicos Is</option>
                                    <option value="Tuvalu">Tuvalu</option>
                                    <option value="Uganda">Uganda</option>
                                    <option value="United Kingdom">United Kingdom</option>
                                    <option value="Ukraine">Ukraine</option>
                                    <option value="United Arab Erimates">United Arab Emirates</option>
                                    <option value="United States of America">United States of America</option>
                                    <option value="Uraguay">Uruguay</option>
                                    <option value="Uzbekistan">Uzbekistan</option>
                                    <option value="Vanuatu">Vanuatu</option>
                                    <option value="Vatican City State">Vatican City State</option>
                                    <option value="Venezuela">Venezuela</option>
                                    <option value="Vietnam">Vietnam</option>
                                    <option value="Virgin Islands (Brit)">Virgin Islands (Brit)</option>
                                    <option value="Virgin Islands (USA)">Virgin Islands (USA)</option>
                                    <option value="Wake Island">Wake Island</option>
                                    <option value="Wallis & Futana Is">Wallis & Futana Is</option>
                                    <option value="Yemen">Yemen</option>
                                    <option value="Zaire">Zaire</option>
                                    <option value="Zambia">Zambia</option>
                                    <option value="Zimbabwe">Zimbabwe</option>
                                </select>

                                <button id="findloc" type="button" onclick="findlocation()">Find your location</button><br><br> 

                                <label for="city" >* City : </label>
                                <input type="text" id="city" onchange="removeMap()" name="city" pattern=".{3,50}" title="Must have 3-50 characters" required>
                                <span id="locationerror"></span><br><br> 
                                <label id="addname" for="addressname">* Address Name : </label>
                                <input type="text" name="addressname" onchange="removeMap()" id="addressname" pattern="[a-zA-z]{5,50}" title="Must be a word with 5-50 characters" required><br><br> 
                                <label id="addnumber" for="addressnumber">* Address Number : </label>
                                <input type="number" name="addressnumber" onchange="removeMap()" id="addressnumber" min=1 step="1" required><br><br> 
                                <label id="addcode" for="addresscode">* Address Code : </label>
                                <input type="number" name="addresscode" id="addresscode" min=1 step="1" required><br><br>
                                <button id="openmap" onclick="Api(true);">Open Map</button><br><br>

                                <label for="phone">* Phone : </label>
                                <input type="tel" id="phone" name="phone" pattern="[0-9]{1,14}" title="Max 14 numbers" required><br><br> 

                                <label for="height">Height : </label>
                                <input type="number" id="height" name="height" min="100" max="250" step="1" title="Must be an integer between 100-250"><br><br>

                                <label for="weight">Weight : </label>
                                <input type="number" id="weight" name="weight" min="20.00" max="300.00" step="0.01" title="Must be a number between 20-300"><br><br>


                                <p>* Voluntary Blood Donor : </p>
                                <input type="radio" id="Yes" value="1" name="blood" value required>
                                <label for="Yes"> Yes </label>
                                <input type="radio" id="No" value="0" name="blood" value required>
                                <label for="No"> No </label><br><br>

                                <label for="bloodteam" >* Select blood type: </label>
                                <select id="bloodteam" name="bloodteam" required>
                                    <option value="">Choose</option>
                                    <option value="A-">A-</option>
                                    <option value="A+">A+</option>
                                    <option value="B-">B-</option>
                                    <option value="B+">B+</option>
                                    <option value="AB-">AB-</option>
                                    <option value="AB+">AB+</option>
                                    <option value="0-">0-</option>
                                    <option value="0+">0+</option>
                                    <option value="Unknown">Unknown</option>
                                </select><br><br>

                                <label for="agree">* I agree with terms : </label>
                                <input type="checkbox" id="agree" name="agree" required><br><br>

                                <input type="button" value="Sign up" onclick="testcheckbox();Api(false);">

                            </form>
                        </div>
                       

                        <div id="userlogin" class="col-sm-6">
                            <h3 id="simpleuserhead">Simple User log-in</h3><br>
                            <form id="loginuser">
                                <label for="usernamelog">Username : </label>
                                <input type="text" id="usernamelogin" name="usernamelog"><br><br>
                                <label for="passwordlog">Password : </label>
                                <input type="password" id="userpasslogin" name="passwordlog"><br><br>
                                <input type="button" value="login" onclick="GetUser(true);">
                            </form>
                        </div>
                        <div id="userlogin" class="col-sm-6">
                            <h3 id="simpleuserhead">Unregistered user</h3><br>
                            <div>
                                <button value="false" id="docButton" onclick="showDocMap()">Available Doctors</button>
                                <div id="map_container"></div>
                            </div>
                            <div>
                                <a href="https://www.vrisko.gr/efimeries-farmakeion/irakleio" target="_blank"><img src="https://www.vrisko.gr/graphlink/Pharmacies/image/468x60_Banner_n/?Region=irakleio&NativeRegion=%ce%97%cf%81%ce%ac%ce%ba%ce%bb%ce%b5%ce%b9%ce%bf&" border="0" alt="Εφημερεύοντα Φαρμακεία Ηράκλειο" /></a>
                                <a href="https://www.vrisko.gr/efimeries-nosokomeion?SelectedCity=hrakleio" target="_blank"><img src="https://www.vrisko.gr/graphlink/Hospitals/image/468x60_Banner_n/?Prefecture=hrakleio&NativePrefecture=%ce%97%ce%a1%ce%91%ce%9a%ce%9b%ce%95%ce%99%ce%9f&" border="0" alt="Εφημερεύοντα Νοσοκομεία ΗΡΑΚΛΕΙΟ" /></a>
                               <div>
                                <a href="https://www.ekab.gr/files/entypa/EKAB-protes-voithies.pdf">Πρώτες βοήθειες</a>
                               </div> 
                               <div>
                                <a href="https://www.venizeleio.gr/">Βενιζέλειο Νοσοκομείο</a>
                                </div>
                                <div>
                                <a href="https://covid19.gov.gr/">Covid-19</a>
                                </div>
                            </div>
                        </div>
                       
                      
                    </div>
                  
                </div>
                
            </div>
        </div><br>

        <div id="container2"></div>
        <div id="container3"></div>
        
       
        <div id="mez"></div>
        <div id="viz" style="width: 900px; height: 300px;"></div>
        <div id="usermess"></div>
        <div id="logoutbutt"></div>
    </body>
    <script type="text/javascript">

        function calendarSettings() {
            var headerHtml = $("#material-header-holder .ui-datepicker-material-header");

            var changeMaterialHeader = function (header, date) {
                var year = date.format('YYYY');
                var month = date.format('MMM');
                var dayNum = date.format('D');
                var isoDay = date.isoWeekday();

                var weekday = new Array(7);
                weekday[1] = "Monday";
                weekday[2] = "Tuesday";
                weekday[3] = "Wednesday";
                weekday[4] = "Thursday";
                weekday[5] = "Friday";
                weekday[6] = "Saturday";
                weekday[7] = "Sunday";

                $('.ui-datepicker-material-day', header).text(weekday[isoDay]);
                $('.ui-datepicker-material-year', header).text(year);
                $('.ui-datepicker-material-month', header).text(month);
                $('.ui-datepicker-material-day-num', header).text(dayNum);
            };

            $.datepicker._selectDateOverload = $.datepicker._selectDate;
            $.datepicker._selectDate = function (id, dateStr) {
                var target = $(id);
                var inst = this._getInst(target[0]);
                inst.inline = true;
                $.datepicker._selectDateOverload(id, dateStr);
                inst.inline = false;
                this._updateDatepicker(inst);

                headerHtml.remove();
                $(".ui-datepicker").prepend(headerHtml);
            };

            $("input[data-type='date']").on("focus", function () {
                //var date;
                //if (this.value == "") {
                //  date = moment();
                //} else {
                //  date = moment(this.value, 'MM/DD/YYYY');
                //}

                $(".ui-datepicker").prepend(headerHtml);
                //$(this).datepicker._selectDate(this, date);
            });

            $("input[data-type='date']").datepicker({
                showButtonPanel: true,
                closeText: 'OK',
                onSelect: function (date, inst) {
                    changeMaterialHeader(headerHtml, moment(date, 'MM/DD/YYYY'));
                }
            });

            changeMaterialHeader(headerHtml, moment());
            $('input').datepicker('show');
        }
    </script>

    <script type="text/javascript">
       
    </script>
</html>
