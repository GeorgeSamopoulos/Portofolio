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
 * @author GS
 */
public class getBloodTestsData extends HttpServlet {

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
            int flag = Integer.parseInt(request.getParameter("flag"));
            //System.out.println("ok");
            SimpleUser u = us.databaseToSimpleUser(username, password);
            EditBloodTestTable bt = new EditBloodTestTable();
            BloodTest[] arbt = bt.databaseToBloodTestAmka(u.getAmka());
            //System.out.println("ok");
            if (flag == 1) {
                int i = 0;
                out.println("<h3>Blood Table :</h3><br>");
                out.println("<table id=\"bloodtable\">");
                out.println("<tr>");
                while (arbt[i] != null) {
                    out.println("<th>");
                    out.println(arbt[i].getTest_date());
                    out.println("</th>");
                    i++;
                }
                out.println("</tr>");

                i = 0;
                out.println("<tr>");
                double currv = 0;
                while (arbt[i] != null) {
                    out.println("<td>");
                    if (i != 0) {
                        double temp = arbt[i].getCholesterol() - currv;
                        out.println("cholesterol:" + arbt[i].getCholesterol() + " (" + temp + ")");
                    } else {
                        out.println("cholesterol:" + arbt[i].getCholesterol());
                    }
                    currv = arbt[i].getCholesterol();
                    out.println("</td>");
                    i++;
                }
                out.println("</tr>");

                i = 0;
                out.println("<tr>");
                currv = 0;
                while (arbt[i] != null) {
                    out.println("<td>");
                    if (i != 0) {
                        double temp = arbt[i].getIron() - currv;
                        out.println("iron:" + arbt[i].getIron() + " (" + temp + ")");
                    } else {
                        out.println("iron:" + arbt[i].getIron());
                    }
                    currv = arbt[i].getIron();
                    out.println("</td>");
                    i++;
                }
                out.println("</tr>");

                i = 0;
                out.println("<tr>");
                currv = 0;
                while (arbt[i] != null) {
                    out.println("<td>");
                    if (i != 0) {
                        double temp = arbt[i].getBlood_sugar() - currv;
                        out.println("blood sugar:" + arbt[i].getBlood_sugar() + " (" + temp + ")");
                    } else {
                        out.println("blood sugar:" + arbt[i].getBlood_sugar());
                    }
                    currv = arbt[i].getBlood_sugar();
                    out.println("</td>");
                    i++;
                }
                out.println("</tr>");

                i = 0;
                out.println("<tr>");
                currv = 0;
                while (arbt[i] != null) {
                    out.println("<td>");
                    if (i != 0) {
                        double temp = arbt[i].getVitamin_d3() - currv;
                        out.println("vitamin_d3:" + arbt[i].getVitamin_d3() + " (" + temp + ")");
                    } else {
                        out.println("vitamin_d3:" + arbt[i].getVitamin_d3());
                    }
                    currv = arbt[i].getVitamin_d3();
                    out.println("</td>");
                    i++;
                }
                out.println("</tr>");

                i = 0;
                out.println("<tr>");
                currv = 0;
                while (arbt[i] != null) {
                    out.println("<td>");
                    if (i != 0) {
                        double temp = arbt[i].getVitamin_b12() - currv;
                        out.println("vitamin_b12:" + arbt[i].getVitamin_b12() + " (" + temp + ")");
                    } else {
                        out.println("vitamin_b12:" + arbt[i].getVitamin_b12());
                    }
                    currv = arbt[i].getVitamin_b12();
                    out.println("</td>");
                    i++;
                }
                out.println("</tr>");

                out.println("</table>");
            } else {
                out.println("<label for=\"mez\">Choose a measurement:</label>");

                String s = "<input type=\"radio\" name=\"mez\" value=\"blood_sugar\" checked>Blood Sugar";
                s += "<input type=\"radio\" name=\"mez\" value=\"cholesterol\">Cholesterol";
                s += "<input type=\"radio\" name=\"mez\" value=\"vitamin_d3\">Vitamin d3";
                s += "<input type=\"radio\" name=\"mez\" value=\"vitamin_b12\">Vitamin b12";
                s += "<input type=\"radio\" name=\"mez\" value=\"iron\">Iron";

                out.println(s);
                out.println("<input type=\"button\" value=\"Get\" onclick=\"GetGraphUser()\">");
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
