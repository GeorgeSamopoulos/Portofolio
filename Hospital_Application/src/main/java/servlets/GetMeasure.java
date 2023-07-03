/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import database.tables.EditBloodTestTable;
import database.tables.EditSimpleUserTable;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import mainClasses.BloodTest;
import mainClasses.SimpleUser;

/**
 *
 * @author GS
 */
public class GetMeasure extends HttpServlet {

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
        try (PrintWriter out = response.getWriter()) {
            int id = Integer.parseInt(request.getParameter("id"));
            String mes = request.getParameter("mez");
            EditSimpleUserTable us = new EditSimpleUserTable();
            SimpleUser u = us.databaseToSimpleUserId(id);
            String amka = u.getAmka();
            EditBloodTestTable bt = new EditBloodTestTable();
            BloodTest abt[] = bt.databaseToBloodTestAmka(amka);
            System.out.println(mes);
            if (mes.equals("blood_sugar")) {
                int i = 0;
                System.out.println("ok");
                while (abt[i] != null) {
                    String val = abt[i].getTest_date()+":"+String.valueOf(abt[i].getBlood_sugar()) + " ";
                    out.println(val);
                    i++;
                }
            } else if (mes.equals("iron")) {
                int i = 0;
                while (abt[i] != null) {
                    String val = abt[i].getTest_date()+":"+String.valueOf(abt[i].getIron()) + " ";
                    out.println(val);
                    i++;
                }
            } else if (mes.equals("cholesterol")) {
                int i = 0;
                while (abt[i] != null) {
                    String val = abt[i].getTest_date()+":"+String.valueOf(abt[i].getCholesterol()) + " ";
                    out.println(val);
                    i++;
                }
            } else if (mes.equals("vitamin_d3")) {
                int i = 0;
                while (abt[i] != null) {
                    String val = abt[i].getTest_date()+":"+String.valueOf(abt[i].getVitamin_d3()) + " ";
                    out.println(val);
                    i++;
                }
            } else if (mes.equals("vitamin_b12")) {
                int i = 0;
                while (abt[i] != null) {
                    String val = abt[i].getTest_date()+":"+String.valueOf(abt[i].getVitamin_b12()) + " ";
                    out.println(val);
                    i++;
                }
            }
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

}
