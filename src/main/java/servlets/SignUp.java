/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */

package servlets;

import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import database.tables.*;
import mainClasses.*;

/**
 *
 * @author GS
 */
@WebServlet(name="SignUp", urlPatterns={"/SignUp"})
public class SignUp extends HttpServlet {
   
    /** 
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code> methods.
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
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        
        

        try(PrintWriter out = response.getWriter()){
           
           String username = request.getParameter("username");
            String email = request.getParameter("email");
            String amka = request.getParameter("amka");
            String type = request.getParameter("usertype");
           if(type.compareTo("Doctor")==0){
                Doctor ndc = new Doctor();
                ndc.setUsername(username);    
                ndc.setEmail(email);
                ndc.setAmka(amka);
                ndc.setAddress(request.getParameter("addressname")+" "+request.getParameter("addressnumber"));
                ndc.setGender(request.getParameter("sex"));
                ndc.setFirstname(request.getParameter("first name"));
                ndc.setLastname(request.getParameter("last name"));
                ndc.setPassword(request.getParameter("password"));
                ndc.setBirthdate(request.getParameter("birthday"));
                ndc.setCountry(request.getParameter("country"));
                ndc.setCity(request.getParameter("city"));
                ndc.setTelephone(request.getParameter("phone"));
                ndc.setBlooddonor(Integer.parseInt(request.getParameter("blood")));
                ndc.setBloodtype(request.getParameter("bloodteam"));
                ndc.setHeight(Integer.parseInt(request.getParameter("height")));
                ndc.setWeight(Double.parseDouble(request.getParameter("weight")));
               ndc.setLat(Double.parseDouble(request.getParameter("lat")));
               ndc.setLon(Double.parseDouble(request.getParameter("lon")));
                ndc.setDoctor_info(request.getParameter("doctortext"));
                ndc.setSpecialty(request.getParameter("doctorspec"));
               ndc.setCertified(0);
                EditDoctorTable dt= new EditDoctorTable();
                String j = dt.doctorToJSON(ndc);
               dt.addDoctorFromJSON(j);
               response.addHeader("Message","Your sign up completed successfully , but it must be verified by admin");
               out.println(j);
           }else{
                SimpleUser nsu = new SimpleUser();
                nsu.setUsername(username);
                nsu.setEmail(email);
                nsu.setAmka(amka);
                nsu.setAddress(request.getParameter("addressname")+" "+request.getParameter("addressnumber"));
                nsu.setGender(request.getParameter("sex"));
                nsu.setFirstname(request.getParameter("first name"));
                nsu.setLastname(request.getParameter("last name"));
                nsu.setPassword(request.getParameter("password"));
                nsu.setBirthdate(request.getParameter("birthday"));
                nsu.setCountry(request.getParameter("country"));
                nsu.setCity(request.getParameter("city"));
                nsu.setTelephone(request.getParameter("phone"));
                nsu.setBlooddonor(Integer.parseInt(request.getParameter("blood")));
                nsu.setBloodtype(request.getParameter("bloodteam"));
                nsu.setHeight(Integer.parseInt(request.getParameter("height")));
                nsu.setWeight(Double.parseDouble(request.getParameter("weight")));
               nsu.setLat(Double.parseDouble(request.getParameter("lat")));
               nsu.setLon(Double.parseDouble(request.getParameter("lon")));

                EditSimpleUserTable st  = new EditSimpleUserTable();
                String j = st.simpleUserToJSON(nsu);
                st.addSimpleUserFromJSON(j);
                response.addHeader("Message","Your sign up completed successfully");
                out.println(j);
           }
           out.close();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(SignUp.class.getName()).log(Level.SEVERE, null, ex);
        }
        response.setStatus(200);
    }
        
        //processRequest(request, response);
} 

   

