/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import database.tables.*;
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

/**
 *
 * @author GS
 */
public class DoneRandevouz extends HttpServlet {

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
            EditRandevouzTable tu = new EditRandevouzTable();
            EditSimpleUserTable us = new EditSimpleUserTable();
            Randevouz r = tu.databaseToRandevouz(id);
            if (r == null) {
                response.setStatus(404);
                return;
            }

            int uid = r.getUser_id();
            SimpleUser u = us.databaseToSimpleUserId(uid);
            if (u == null) {
                response.setStatus(404);
                return;
            }
            String amka = u.getAmka();
            EditBloodTestTable bt = new EditBloodTestTable();
            BloodTest arb[] = bt.databaseToBloodTestAmka(amka);
            int i = 0;
            out.println("<br><br>");
            while (arb[i] != null) {
                out.println("<div id=" + i + ">");
                out.println("Date : " + arb[i].getTest_date());
                out.println(" medical center : " + arb[i].getMedical_center());
                out.println(" blood sugar : " + arb[i].getBlood_sugar() + "(" + arb[i].getBlood_sugar_level() + ")");
                out.println(" cholesterol : " + arb[i].getCholesterol() + "(" + arb[i].getCholesterol_level() + ")");
                out.println(" iron : " + arb[i].getIron() + "(" + arb[i].getIron_level() + ")");
                out.println(" vitamin_d3 : " + arb[i].getVitamin_d3() + "(" + arb[i].getVitamin_d3_level() + ")");
                out.println(" vitamin_b12 : " + arb[i].getVitamin_b12() + "(" + arb[i].getVitamin_b12_level() + ")");
                out.println("</div><br>");
                i++;
            }
            HttpSession session = request.getSession();
            String username = (String) session.getAttribute("name");
            String password = (String) session.getAttribute("pass");

            EditDoctorTable dt = new EditDoctorTable();
            Doctor d = dt.databaseToDoctor(username,password);
            int did = d.getDoctor_id();

            EditMessageTable mt = new EditMessageTable();
            Message mar []= mt.databaseToMessageId(did,uid);
            i=0;
            while(mar[i]!=null){
                if(mar[i].getSender().equals("user")){
                    out.println("<div id=mess" + i + ">");
                    out.println(mar[i].getMessage());
                    out.println("</div><br>");
                }
                i++;
            }
            out.println("<label for=\""+"AnswearBox"+"\">Send Answear:");
            out.println("</label>");
            out.println("<textarea id=\""+"AnswearBox"+"\" name=\""+"AnswearBox"+"\">");
            out.println("</textarea>");
            out.println("<input type=\"button\" id=\"answear\" value=\"Answear\" onclick=\"sendAnswear("+uid+")\"/><br>");
            out.println("<label for=\"mez\">Choose a measurement:</label>");
            
            String s = "<input type=\"radio\" name=\"mez\" value=\"blood_sugar\" checked>Blood Sugar";
            s+= "<input type=\"radio\" name=\"mez\" value=\"cholesterol\">Cholesterol";
            s+= "<input type=\"radio\" name=\"mez\" value=\"vitamin_d3\">Vitamin d3";
            s+= "<input type=\"radio\" name=\"mez\" value=\"vitamin_b12\">Vitamin b12";
            s+= "<input type=\"radio\" name=\"mez\" value=\"iron\">Iron";
           
            out.println(s);
            
           
            out.println("<input type=\"button\" value=\"Get\" onclick=\"GetGraph("+uid+")\">");
            
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
