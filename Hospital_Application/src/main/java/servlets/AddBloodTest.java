/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import database.tables.*;
import mainClasses.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author SAMO
 */
public class AddBloodTest extends HttpServlet {

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
        try (PrintWriter out = response.getWriter()) {
            double cholesterol = Double.parseDouble(request.getParameter("cholesterol"));
            double vitamin_d3 = Double.parseDouble(request.getParameter("vitamin_d3"));
            double vitamin_b12 = Double.parseDouble(request.getParameter("vitamin_b12"));
            double iron = Double.parseDouble(request.getParameter("iron"));
            double sugar = Double.parseDouble(request.getParameter("bloodsugar"));
            String medicalCenter = request.getParameter("medicalCenter");
            String date = request.getParameter("dateTest");
            EditBloodTestTable bt = new EditBloodTestTable();
            BloodTest nb = new BloodTest();
            nb.setCholesterol(cholesterol);
            nb.setIron(iron);
            nb.setBlood_sugar(sugar);
            nb.setVitamin_b12(vitamin_b12);
            nb.setVitamin_d3(vitamin_d3);
            nb.setMedical_center(medicalCenter);
            nb.setTest_date(date);

            EditSimpleUserTable us = new EditSimpleUserTable();
            HttpSession session = request.getSession();
            String username = (String) session.getAttribute("name");
            String password = (String) session.getAttribute("pass");

            SimpleUser u = us.databaseToSimpleUser(username, password);
            String amka = u.getAmka();

            nb.setAmka(amka);
            nb.setValues();
            bt.createNewBloodTest(nb);

        } catch (SQLException ex) {

        } catch (ClassNotFoundException ex) {

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
