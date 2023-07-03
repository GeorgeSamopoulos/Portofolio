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
import java.sql.SQLException;
import database.tables.*;

/**
 *
 * @author GS
 */
@WebServlet(name="TestUser", urlPatterns={"/TestUser"})
public class TestUser extends HttpServlet {
   
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
        String username = request.getParameter("username");
        String email = request.getParameter("email");
        String amka = request.getParameter("amka");
        EditDoctorTable dc = new EditDoctorTable();
        try(PrintWriter out = response.getWriter()){
            String rs = dc.databaseToJSONAmka(amka);
            if (rs != null) {
                out.println("Doctor Amka is used");
                response.setStatus(400);
                return;
            }
            rs = dc.databaseToJSONEmail(email);
            if (rs != null) {
                out.println("Doctor Email is used");
                response.setStatus(400);

                return;
            }
            rs = dc.databaseToJSONUsername(username);
            if (rs != null) {
                out.println("Doctor Username is used");
                response.setStatus(400);
                return;
            }


            EditSimpleUserTable us = new EditSimpleUserTable();
            rs = us.databaseAmkaUserToJSON(amka);
            if (rs != null) {
                out.println("Amka is used");
                response.setStatus(400);
                 return;
            }
            rs = us.databaseEmailUserToJSON(email);
            if (rs != null) {
                out.println("Email is used");
                response.setStatus(400);
                return;
            }
            rs = us.databaseUsernameUserToJSON(username);
            if (rs != null) {
                out.println("Username is used");
                response.setStatus(400);
                return;
            }
            out.println("OK");
            response.setStatus(200);
        }catch (SQLException ex) {
            Logger.getLogger(SignUp.class.getName()).log(Level.SEVERE, null, ex);
        }catch (ClassNotFoundException ex) {
            Logger.getLogger(SignUp.class.getName()).log(Level.SEVERE, null, ex);
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
