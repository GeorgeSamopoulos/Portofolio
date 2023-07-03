/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */

package servlets;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import database.tables.*;
import mainClasses.*;
import java.io.IOException;
import java.util.Date;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.logging.Logger;
import java.util.logging.Level;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author GS
 */
@WebServlet(name="UpdateData", urlPatterns={"/UpdateData"})
public class UpdateData extends HttpServlet {
   
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

        try{
            EditSimpleUserTable dct = new EditSimpleUserTable();
            String username=request.getParameter("usernameinfo");
            String firstname=request.getParameter("firstnameinfo");
            String lastname=request.getParameter("lastnameinfo");
            String email=request.getParameter("emailinfo");
            String password=request.getParameter("passwordinfo");
            String city=request.getParameter("cityinfo");
            String country=request.getParameter("countryinfo");
            String address=request.getParameter("addressinfo");
            Date date=new SimpleDateFormat("yyyy-MM-dd").parse(request.getParameter("birthdayinfo"));
            String tel=request.getParameter("telephoneinfo");
            String bloodtype=request.getParameter("bloodtypeinfo");
            double weight=Double.parseDouble(request.getParameter("weightinfo"));
            int height=Integer.parseInt(request.getParameter("heightinfo"));
            dct.updateDataSimpleUser(username,date,firstname,lastname,email,password,city,country,address,tel,bloodtype,weight ,height);
        
        }catch(SQLException ex){
            Logger.getLogger(UpdateData.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(UpdateData.class.getName()).log(Level.SEVERE, null, ex);
        }catch (ParseException e) {
            e.printStackTrace();
        }
    } 

    /** 
     * Handles the HTTP <code>POST</code> method.
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
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
