/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import database.tables.EditDoctorTable;
import database.tables.EditSimpleUserTable;
import database.tables.EditTreatmentTable;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import mainClasses.*;

/**
 *
 * @author GS
 */
@WebServlet(name = "AddTreatment", urlPatterns = {"/AddTreatment"})
public class AddTreatment extends HttpServlet {

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
        
        try(PrintWriter out = response.getWriter()){
            String last = request.getParameter("lastnameT");
            String first = request.getParameter("firstnameT");
            String treat = request.getParameter("treatT");
            String start = request.getParameter("startT");
            String end = request.getParameter("endT");
            int bid = Integer.parseInt(request.getParameter("bloodId"));
            System.out.println(start);
            System.out.println(end);
            
            HttpSession session = request.getSession();
            String name = (String)session.getAttribute("name");
            String pass = (String)session.getAttribute("pass");
            
            EditDoctorTable dt = new EditDoctorTable();
            Doctor d = dt.databaseToDoctor(name, pass);
            int did = d.getDoctor_id();
            
            EditSimpleUserTable us = new EditSimpleUserTable();
            int uid = us.getUserId(first, last);
            
            Treatment t = new Treatment();
            t.setDoctor_id(did);
            t.setEnd_date(end);
            t.setStart_date(start);
            t.setUser_id(uid);
            t.setTreatment_text(treat);
            t.setBloodtest_id(bid);
            
            
            EditTreatmentTable tt =new EditTreatmentTable();
            tt.createNewTreatment(t);
            
            
        }catch (SQLException ex) {
            response.setStatus(404);
            Logger.getLogger(LoginUser.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            response.setStatus(404);
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

}
