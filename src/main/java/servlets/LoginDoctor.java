/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import mainClasses.*;
import database.tables.*;
/**
 *
 * @author SAMO
 */
public class LoginDoctor extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //processRequest(request, response);

        try (PrintWriter out = response.getWriter()) {;
            //HttpSession session = request.getSession();
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            System.out.println(username);            
            System.out.println(password);

            HttpSession session = request.getSession();
            session.setAttribute("name", username);
            session.setAttribute("pass", password);
            EditDoctorTable tu = new EditDoctorTable();
            Doctor us = tu.databaseToDoctor(username, password);
            out.println(LoginData(us) + "<br>" /*+ LoadDoctors() + "<br>" + LogoutButt()*/);
            out.close();
        } catch (SQLException ex) {
            Logger.getLogger(LoginUser.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(LoginUser.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

    public String LoginData(Doctor us) {
        String result = "<h3>Doctor's Data</h3>";
        result += "<form id=\"UserData\">";

        result += "<label for=\"usernameinfo\">Username : </label>";
        result += "<input type=\"text\" id=\"usernameinfo\" name=\"usernameinfo\" value=\"" + us.getUsername() + "\" readonly><br>";
        result += "<label for=\"amkainfo\">Amka : </label>";
        result += "<input type=\"text\" id=\"amkainfo\" name=\"amkainfo\" value=\"" + us.getAmka() + "\" readonly><br>";
        result += "<label for=\"emailinfo\" >* Email : </label>"
                + "<input type=\"email\" id=\"emailinfo\" name=\"emailinfo\" value=\"" + us.getEmail() + "\" pattern=\"[a-z0-9]+@+[a-z0-9]+\\.+[a-z]{2,}\" title=\"Must be legal\" required><br>";
        result += "<label for=\"passwordinfo\">Password : </label>";
        result += "<input type=\"password\" id=\"passwordinfo\" name=\"passwordinfo\" pattern=\"(?=.*\\d)(?=.*[a-zA-Z])(?=.*[!@#$%^&*()]).{8,15}\" title=\"Must have 8-15 characters with min a character , a number and a symbol\" value=\"" + us.getPassword() + "\" ><br>";
        result += "<label for=\"firstnameinfo\">First name : </label>";
        result += "<input type=\"text\" id=\"firstnameinfo\" name=\"firstnameinfo\" pattern=\".{3,30}\" title=\"Must have 3-30 characters\" value=\"" + us.getFirstname() + "\" ><br>";
        result += "<label for=\"lastnameinfo\">First name : </label>";
        result += "<input type=\"text\" id=\"lastnameinfo\" name=\"lastnameinfo\" pattern=\".{3,30}\" title=\"Must have 3-30 characters\" value=\"" + us.getLastname() + "\" ><br>";
        result += "<label for=\"cityinfo\">City : </label>";
        result += "<input type=\"text\" id=\"cityinfo\" name=\"cityinfo\" pattern=\".{3,50}\" title=\"Must have 3-50 characters\" value=\"" + us.getCity() + "\" ><br>";
        result += "<label for=\"addressinfo\">Address : </label>";
        result += "<input type=\"text\" id=\"addressinfo\" name=\"addressinfo\" value=\"" + us.getAddress() + "\"><br>";

        result += "<label for=\"telephoneinfo\">Phone : </label>";
        result += "<input type=\"text\" id=\"telephoneinfo\" name=\"telephoneinfo\" pattern=\"[0-9]{1,14}\" title=\"Max 14 numbers\" value=\"" + us.getTelephone() + "\" ><br>";
        result += "<label for=\"heightinfo\">Height : </label>"
                + "<input type=\"number\" id=\"heightinfo\" name=\"heightinfo\" value = " + us.getHeight() + " min=\"100\" max=\"250\" step=\"1\" title=\"Must be an integer between 100-250\"><br>"
                + "<label for=\"weightinfo\">Weight : </label>"
                + "<input type=\"number\" id=\"weightinfo\" name=\"weightinfo\" value = " + us.getWeight() + " min=\"20.00\" max=\"300.00\" step=\"0.01\" title=\"Must be a number between 20-300\"><br>";
        result += "<label for=\"birthdayinfo\" >* Birth Day : </label>"
                + "<input type=\"date\" id=\"birthdayinfo\" name=\"birthdayinfo\" value=\"" + us.getBirthdate() + "\" min=\"1920-01-01\" max=\"2005-12-31\" title=\"Wrong Date\" required><br>";
        result += "<label for=\"countryinfo\" >* Country : " + us.getCountry() + "Change to : </label>\n"
                + "<select id=\"countryinfo\"  onchange=\"removeMap()\" name=\"countryinfo\" required>\n"
                + "<option value=\"\">Choose</option>\n"
                + "<option value=\"Afganistan\">Afghanistan</option>\n"
                + "<option value=\"Albania\">Albania</option>\n"
                + "<option value=\"Algeria\">Algeria</option>\n"
                + " <option value=\"American Samoa\">American Samoa</option>\n"
                + "<option value=\"Andorra\">Andorra</option>\n"
                + "<option value=\"Angola\">Angola</option>\n"
                + "<option value=\"Anguilla\">Anguilla</option>\n"
                + "<option value=\"Antigua & Barbuda\">Antigua & Barbuda</option>\n"
                + "<option value=\"Argentina\">Argentina</option>\n"
                + "<option value=\"Armenia\">Armenia</option>\n"
                + "<option value=\"Aruba\">Aruba</option>\n"
                + "<option value=\"Australia\">Australia</option>\n"
                + "<option value=\"Austria\">Austria</option>\n"
                + "<option value=\"Azerbaijan\">Azerbaijan</option>\n"
                + "<option value=\"Bahamas\">Bahamas</option>\n"
                + "<option value=\"Bahrain\">Bahrain</option>\n"
                + "<option value=\"Bangladesh\">Bangladesh</option>\n"
                + "<option value=\"Barbados\">Barbados</option>\n"
                + "<option value=\"Belarus\">Belarus</option>\n"
                + "<option value=\"Belgium\">Belgium</option>\n"
                + "                                <option value=\"Belize\">Belize</option>\n"
                + "                                <option value=\"Benin\">Benin</option>\n"
                + "                                <option value=\"Bermuda\">Bermuda</option>\n"
                + "                                <option value=\"Bhutan\">Bhutan</option>\n"
                + "                                <option value=\"Bolivia\">Bolivia</option>\n"
                + "                                <option value=\"Bonaire\">Bonaire</option>\n"
                + "                                <option value=\"Bosnia & Herzegovina\">Bosnia & Herzegovina</option>\n"
                + "                                <option value=\"Botswana\">Botswana</option>\n"
                + "                                <option value=\"Brazil\">Brazil</option>\n"
                + "                                <option value=\"British Indian Ocean Ter\">British Indian Ocean Ter</option>\n"
                + "                                <option value=\"Brunei\">Brunei</option>\n"
                + "                                <option value=\"Bulgaria\">Bulgaria</option>\n"
                + "                                <option value=\"Burkina Faso\">Burkina Faso</option>\n"
                + "                                <option value=\"Burundi\">Burundi</option>\n"
                + "                                <option value=\"Cambodia\">Cambodia</option>\n"
                + "                                <option value=\"Cameroon\">Cameroon</option>\n"
                + "                                <option value=\"Canada\">Canada</option>\n"
                + "                                <option value=\"Canary Islands\">Canary Islands</option>\n"
                + "                                <option value=\"Cape Verde\">Cape Verde</option>\n"
                + "                                <option value=\"Cayman Islands\">Cayman Islands</option>\n"
                + "                                <option value=\"Central African Republic\">Central African Republic</option>\n"
                + "                                <option value=\"Chad\">Chad</option>\n"
                + "                                <option value=\"Channel Islands\">Channel Islands</option>\n"
                + "                                <option value=\"Chile\">Chile</option>\n"
                + "                                <option value=\"China\">China</option>\n"
                + "                                <option value=\"Christmas Island\">Christmas Island</option>\n"
                + "                                <option value=\"Cocos Island\">Cocos Island</option>\n"
                + "                                <option value=\"Colombia\">Colombia</option>\n"
                + "                                <option value=\"Comoros\">Comoros</option>\n"
                + "                                <option value=\"Congo\">Congo</option>\n"
                + "                                <option value=\"Cook Islands\">Cook Islands</option>\n"
                + "                                <option value=\"Costa Rica\">Costa Rica</option>\n"
                + "                                <option value=\"Cote DIvoire\">Cote DIvoire</option>\n"
                + "                                <option value=\"Croatia\">Croatia</option>\n"
                + "                                <option value=\"Cuba\">Cuba</option>\n"
                + "                                <option value=\"Curaco\">Curacao</option>\n"
                + "                                <option value=\"Cyprus\">Cyprus</option>\n"
                + "                                <option value=\"Czech Republic\">Czech Republic</option>\n"
                + "                                <option value=\"Denmark\">Denmark</option>\n"
                + "                                <option value=\"Djibouti\">Djibouti</option>\n"
                + "                                <option value=\"Dominica\">Dominica</option>\n"
                + "                                <option value=\"Dominican Republic\">Dominican Republic</option>\n"
                + "                                <option value=\"East Timor\">East Timor</option>\n"
                + "                                <option value=\"Ecuador\">Ecuador</option>\n"
                + "                                <option value=\"Egypt\">Egypt</option>\n"
                + "                                <option value=\"El Salvador\">El Salvador</option>\n"
                + "                                <option value=\"Equatorial Guinea\">Equatorial Guinea</option>\n"
                + "                                <option value=\"Eritrea\">Eritrea</option>\n"
                + "                                <option value=\"Estonia\">Estonia</option>\n"
                + "                                <option value=\"Ethiopia\">Ethiopia</option>\n"
                + "                                <option value=\"Falkland Islands\">Falkland Islands</option>\n"
                + "                                <option value=\"Faroe Islands\">Faroe Islands</option>\n"
                + "                                <option value=\"Fiji\">Fiji</option>\n"
                + "                                <option value=\"Finland\">Finland</option>\n"
                + "                                <option value=\"France\">France</option>\n"
                + "                                <option value=\"French Guiana\">French Guiana</option>\n"
                + "                                <option value=\"French Polynesia\">French Polynesia</option>\n"
                + "                                <option value=\"French Southern Ter\">French Southern Ter</option>\n"
                + "                                <option value=\"Gabon\">Gabon</option>\n"
                + "                                <option value=\"Gambia\">Gambia</option>\n"
                + "                                <option value=\"Georgia\">Georgia</option>\n"
                + "                                <option value=\"Germany\">Germany</option>\n"
                + "                                <option value=\"Ghana\">Ghana</option>\n"
                + "                                <option value=\"Gibraltar\">Gibraltar</option>\n"
                + "                                <option value=\"Great Britain\">Great Britain</option>\n"
                + "                                <option value=\"Greece\" selected>Greece</option>\n"
                + "                                <option value=\"Greenland\">Greenland</option>\n"
                + "                                <option value=\"Grenada\">Grenada</option>\n"
                + "                                <option value=\"Guadeloupe\">Guadeloupe</option>\n"
                + "                                <option value=\"Guam\">Guam</option>\n"
                + "                                <option value=\"Guatemala\">Guatemala</option>\n"
                + "                                <option value=\"Guinea\">Guinea</option>\n"
                + "                                <option value=\"Guyana\">Guyana</option>\n"
                + "                                <option value=\"Haiti\">Haiti</option>\n"
                + "                                <option value=\"Hawaii\">Hawaii</option>\n"
                + "                                <option value=\"Honduras\">Honduras</option>\n"
                + "                                <option value=\"Hong Kong\">Hong Kong</option>\n"
                + "                                <option value=\"Hungary\">Hungary</option>\n"
                + "                                <option value=\"Iceland\">Iceland</option>\n"
                + "                                <option value=\"Indonesia\">Indonesia</option>\n"
                + "                                <option value=\"India\">India</option>\n"
                + "                                <option value=\"Iran\">Iran</option>\n"
                + "                                <option value=\"Iraq\">Iraq</option>\n"
                + "                                <option value=\"Ireland\">Ireland</option>\n"
                + "                                <option value=\"Isle of Man\">Isle of Man</option>\n"
                + "                                <option value=\"Israel\">Israel</option>\n"
                + "                                <option value=\"Italy\">Italy</option>\n"
                + "                                <option value=\"Jamaica\">Jamaica</option>\n"
                + "                                <option value=\"Japan\">Japan</option>\n"
                + "                                <option value=\"Jordan\">Jordan</option>\n"
                + "                                <option value=\"Kazakhstan\">Kazakhstan</option>\n"
                + "                                <option value=\"Kenya\">Kenya</option>\n"
                + "                                <option value=\"Kiribati\">Kiribati</option>\n"
                + "                                <option value=\"Korea North\">Korea North</option>\n"
                + "                                <option value=\"Korea Sout\">Korea South</option>\n"
                + "                                <option value=\"Kuwait\">Kuwait</option>\n"
                + "                                <option value=\"Kyrgyzstan\">Kyrgyzstan</option>\n"
                + "                                <option value=\"Laos\">Laos</option>\n"
                + "                                <option value=\"Latvia\">Latvia</option>\n"
                + "                                <option value=\"Lebanon\">Lebanon</option>\n"
                + "                                <option value=\"Lesotho\">Lesotho</option>\n"
                + "                                <option value=\"Liberia\">Liberia</option>\n"
                + "                                <option value=\"Libya\">Libya</option>\n"
                + "                                <option value=\"Liechtenstein\">Liechtenstein</option>\n"
                + "                                <option value=\"Lithuania\">Lithuania</option>\n"
                + "                                <option value=\"Luxembourg\">Luxembourg</option>\n"
                + "                                <option value=\"Macau\">Macau</option>\n"
                + "                                <option value=\"Macedonia\">Macedonia</option>\n"
                + "                                <option value=\"Madagascar\">Madagascar</option>\n"
                + "                                <option value=\"Malaysia\">Malaysia</option>\n"
                + "                                <option value=\"Malawi\">Malawi</option>\n"
                + "                                <option value=\"Maldives\">Maldives</option>\n"
                + "                                <option value=\"Mali\">Mali</option>\n"
                + "                                <option value=\"Malta\">Malta</option>\n"
                + "                                <option value=\"Marshall Islands\">Marshall Islands</option>\n"
                + "                                <option value=\"Martinique\">Martinique</option>\n"
                + "                                <option value=\"Mauritania\">Mauritania</option>\n"
                + "                                <option value=\"Mauritius\">Mauritius</option>\n"
                + "                                <option value=\"Mayotte\">Mayotte</option>\n"
                + "                                <option value=\"Mexico\">Mexico</option>\n"
                + "                                <option value=\"Midway Islands\">Midway Islands</option>\n"
                + "                                <option value=\"Moldova\">Moldova</option>\n"
                + "                                <option value=\"Monaco\">Monaco</option>\n"
                + "                                <option value=\"Mongolia\">Mongolia</option>\n"
                + "                                <option value=\"Montserrat\">Montserrat</option>\n"
                + "                                <option value=\"Morocco\">Morocco</option>\n"
                + "                                <option value=\"Mozambique\">Mozambique</option>\n"
                + "                                <option value=\"Myanmar\">Myanmar</option>\n"
                + "                                <option value=\"Nambia\">Nambia</option>\n"
                + "                                <option value=\"Nauru\">Nauru</option>\n"
                + "                                <option value=\"Nepal\">Nepal</option>\n"
                + "                                <option value=\"Netherland Antilles\">Netherland Antilles</option>\n"
                + "                                <option value=\"Netherlands\">Netherlands (Holland, Europe)</option>\n"
                + "                                <option value=\"Nevis\">Nevis</option>\n"
                + "                                <option value=\"New Caledonia\">New Caledonia</option>\n"
                + "                                <option value=\"New Zealand\">New Zealand</option>\n"
                + "                                <option value=\"Nicaragua\">Nicaragua</option>\n"
                + "                                <option value=\"Niger\">Niger</option>\n"
                + "                                <option value=\"Nigeria\">Nigeria</option>\n"
                + "                                <option value=\"Niue\">Niue</option>\n"
                + "                                <option value=\"Norfolk Island\">Norfolk Island</option>\n"
                + "                                <option value=\"Norway\">Norway</option>\n"
                + "                                <option value=\"Oman\">Oman</option>\n"
                + "                                <option value=\"Pakistan\">Pakistan</option>\n"
                + "                                <option value=\"Palau Island\">Palau Island</option>\n"
                + "                                <option value=\"Palestine\">Palestine</option>\n"
                + "                                <option value=\"Panama\">Panama</option>\n"
                + "                                <option value=\"Papua New Guinea\">Papua New Guinea</option>\n"
                + "                                <option value=\"Paraguay\">Paraguay</option>\n"
                + "                                <option value=\"Peru\">Peru</option>\n"
                + "                                <option value=\"Phillipines\">Philippines</option>\n"
                + "                                <option value=\"Pitcairn Island\">Pitcairn Island</option>\n"
                + "                                <option value=\"Poland\">Poland</option>\n"
                + "                                <option value=\"Portugal\">Portugal</option>\n"
                + "                                <option value=\"Puerto Rico\">Puerto Rico</option>\n"
                + "                                <option value=\"Qatar\">Qatar</option>\n"
                + "                                <option value=\"Republic of Montenegro\">Republic of Montenegro</option>\n"
                + "                                <option value=\"Republic of Serbia\">Republic of Serbia</option>\n"
                + "                                <option value=\"Reunion\">Reunion</option>\n"
                + "                                <option value=\"Romania\">Romania</option>\n"
                + "                                <option value=\"Russia\">Russia</option>\n"
                + "                                <option value=\"Rwanda\">Rwanda</option>\n"
                + "                                <option value=\"St Barthelemy\">St Barthelemy</option>\n"
                + "                                <option value=\"St Eustatius\">St Eustatius</option>\n"
                + "                                <option value=\"St Helena\">St Helena</option>\n"
                + "                                <option value=\"St Kitts-Nevis\">St Kitts-Nevis</option>\n"
                + "                                <option value=\"St Lucia\">St Lucia</option>\n"
                + "                                <option value=\"St Maarten\">St Maarten</option>\n"
                + "                                <option value=\"St Pierre & Miquelon\">St Pierre & Miquelon</option>\n"
                + "                                <option value=\"St Vincent & Grenadines\">St Vincent & Grenadines</option>\n"
                + "                                <option value=\"Saipan\">Saipan</option>\n"
                + "                                <option value=\"Samoa\">Samoa</option>\n"
                + "                                <option value=\"Samoa American\">Samoa American</option>\n"
                + "                                <option value=\"San Marino\">San Marino</option>\n"
                + "<option value=\"Sao Tome & Principe\">Sao Tome & Principe</option>\n"
                + "<option value=\"Saudi Arabia\">Saudi Arabia</option>\n"
                + "<option value=\"Senegal\">Senegal</option>\n"
                + " <option value=\"Seychelles\">Seychelles</option>\n"
                + "<option value=\"Sierra Leone\">Sierra Leone</option>\n"
                + "<option value=\"Singapore\">Singapore</option>\n"
                + "<option value=\"Slovakia\">Slovakia</option>\n"
                + " <option value=\"Slovenia\">Slovenia</option>\n"
                + "<option value=\"Solomon Islands\">Solomon Islands</option>\n"
                + "<option value=\"Somalia\">Somalia</option>\n"
                + "<option value=\"South Africa\">South Africa</option>\n"
                + "<option value=\"Spain\">Spain</option>\n"
                + "<option value=\"Sri Lanka\">Sri Lanka</option>\n"
                + "<option value=\"Sudan\">Sudan</option>\n"
                + "<option value=\"Suriname\">Suriname</option>\n"
                + "<option value=\"Swaziland\">Swaziland</option>\n"
                + "<option value=\"Sweden\">Sweden</option>\n"
                + "<option value=\"Switzerland\">Switzerland</option>\n"
                + "<option value=\"Syria\">Syria</option>\n"
                + "<option value=\"Tahiti\">Tahiti</option>\n"
                + "<option value=\"Taiwan\">Taiwan</option>\n"
                + "<option value=\"Tajikistan\">Tajikistan</option>\n"
                + "<option value=\"Tanzania\">Tanzania</option>\n"
                + "<option value=\"Thailand\">Thailand</option>\n"
                + "<option value=\"Togo\">Togo</option>\n"
                + "<option value=\"Tokelau\">Tokelau</option>\n"
                + "<option value=\"Tonga\">Tonga</option>\n"
                + "<option value=\"Trinidad & Tobago\">Trinidad & Tobago</option>\n"
                + "<option value=\"Tunisia\">Tunisia</option>\n"
                + "<option value=\"Turkey\">Turkey</option>\n"
                + "<option value=\"Turkmenistan\">Turkmenistan</option>\n"
                + "<option value=\"Turks & Caicos Is\">Turks & Caicos Is</option>\n"
                + "<option value=\"Tuvalu\">Tuvalu</option>\n"
                + "<option value=\"Uganda\">Uganda</option>\n"
                + "<option value=\"United Kingdom\">United Kingdom</option>\n"
                + "<option value=\"Ukraine\">Ukraine</option>\n"
                + "<option value=\"United Arab Erimates\">United Arab Emirates</option>\n"
                + "<option value=\"United States of America\">United States of America</option>"
                + "<option value=\"Uraguay\">Uruguay</option>"
                + "<option value=\"Uzbekistan\">Uzbekistan</option>"
                + " <option value=\"Vanuatu\">Vanuatu</option>"
                + "<option value=\"Vatican City State\">Vatican City State</option>"
                + "<option value=\"Venezuela\">Venezuela</option>"
                + "<option value=\"Vietnam\">Vietnam</option>"
                + "<option value=\"Virgin Islands (Brit)\">Virgin Islands (Brit)</option>"
                + "<option value=\"Virgin Islands (USA)\">Virgin Islands (USA)</option>"
                + "<option value=\"Wake Island\">Wake Island</option>"
                + "<option value=\"Wallis & Futana Is\">Wallis & Futana Is</option>"
                + "<option value=\"Yemen\">Yemen</option>"
                + "<option value=\"Zaire\">Zaire</option>"
                + "<option value=\"Zambia\">Zambia</option>"
                + "<option value=\"Zimbabwe\">Zimbabwe</option>"
                + "</select><br>";

        result += "<label for=\"bloodteaminfo\" > Blood Type : " + us.getBloodtype() + "   Change to : </label>"
                + "<select id=\"bloodteaminfo\" name=\"bloodteaminfo\" required>"
                + "<option value=\"\">Choose</option>"
                + "<option value=\"A-\">A-</option>"
                + "<option value=\"A+\">A+</option>"
                + "<option value=\"B-\">B-</option>"
                + "<option value=\"B+\">B+</option>"
                + "<option value=\"AB-\">AB-</option>"
                + "<option value=\"AB+\">AB+</option>"
                + "<option value=\"0-\">0-</option>"
                + "<option value=\"0+\">0+</option>"
                + "<option value=\"Unknown\">Unknown</option>"
                + "</select><br>";

        result += "</form>";

        result += "<input type=\"button\" value=\"Change Data\" onclick=\"TestDataDoctor();\">";
        return result;
    }
}
