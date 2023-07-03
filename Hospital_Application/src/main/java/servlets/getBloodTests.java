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
import javax.servlet.http.HttpSession;
import mainClasses.BloodTest;
import mainClasses.SimpleUser;

/**
 *
 * @author SAMO
 */
public class getBloodTests extends HttpServlet {

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
        try (PrintWriter out = response.getWriter()) {;

            //System.out.println("ok");
            EditSimpleUserTable us = new EditSimpleUserTable();
            HttpSession session = request.getSession();
            String username = (String) session.getAttribute("name");
            String password = (String) session.getAttribute("pass");
            //System.out.println("ok");
            SimpleUser u = us.databaseToSimpleUser(username, password);
            EditBloodTestTable bt = new EditBloodTestTable();
            BloodTest[] arbt = bt.databaseToBloodTestAmka(u.getAmka());
            //System.out.println("ok");
            int i = 0;
            out.println("<h3>Blood Tests :</h3><br>");
            while (arbt[i] != null) {

                out.println("<div id=" + arbt[i].getBloodtest_id() + ">");
                out.println("date:" + arbt[i].getTest_date() + "  ");
                out.println("medical center :" + arbt[i].getMedical_center() + "  ");
                out.println("cholesterol:" + arbt[i].getCholesterol() + " (" + arbt[i].getCholesterol_level() + ")  ");
                out.println("vitamin_d3:" + arbt[i].getVitamin_d3() + " (" + arbt[i].getVitamin_d3_level() + ")  ");
                out.println("vitamin_b12:" + arbt[i].getVitamin_b12() + " (" + arbt[i].getVitamin_b12_level() + ")  ");
                out.println("iron:" + arbt[i].getIron() + " (" + arbt[i].getIron_level() + ")  ");
                out.println("</div><br>\n");
                i++;
            }
            //System.out.println("ok");
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
