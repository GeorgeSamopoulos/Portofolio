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
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Date;
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
public class getTreatments extends HttpServlet {

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

            HttpSession session = request.getSession();
            String username = (String) session.getAttribute("name");
            String password = (String) session.getAttribute("pass");

            EditSimpleUserTable us = new EditSimpleUserTable();
            SimpleUser u = us.databaseToSimpleUser(username, password);

            EditTreatmentTable tt = new EditTreatmentTable();

            Treatment[] t = tt.databaseToTreamentUser(u.getUser_id());

            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            String s = dtf.format(now);
            System.out.println(t[0].getEnd_date());
            
            String dates[] = s.split(" ");
            String ndates [] = dates[0].split("/");
            
            Date cd = new Date(Integer.parseInt(ndates[0]),Integer.parseInt(ndates[1]),Integer.parseInt(ndates[2]));
            int i=0;
            
            out.println("<h3>Active Treatments :</h3><br>");
            while(t[i]!=null){
                String tdates [] = t[i].getEnd_date().split("-");
                Date td = new Date(Integer.parseInt(tdates[0]),Integer.parseInt(tdates[1]),Integer.parseInt(tdates[2]));
                System.out.println("ok");
                if(cd.before(td)){
                    out.println("<div id=treat"+t[i].getTreatment_id()+">");
                    out.println("<p> EndTime:"+t[i].getEnd_date()+"  Treatment : "+t[i].getTreatment_text()+"</p>");
                    out.println("</div><br>");
                }
                i++;
            }
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
