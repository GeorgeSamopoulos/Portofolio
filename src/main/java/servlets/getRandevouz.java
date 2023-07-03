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
public class getRandevouz extends HttpServlet {

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
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            /* TODO output your page here. You may use following sample code. */
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet getRandevouz</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet getRandevouz at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
        }
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
        
        try(PrintWriter out = response.getWriter()){;
            //HttpSession session = request.getSession();
            String timestart = request.getParameter("timestart");
            
            String timeend = request.getParameter("timeend");
            System.out.println(timeend);
            EditRandevouzTable tu = new EditRandevouzTable();
            EditSimpleUserTable us = new EditSimpleUserTable();
            Randevouz rs[] = tu.databaseToRandevouzTime(timestart,timeend);
            int i=0;
            while(rs[i]!=null){
                String time = rs[i].getDate_time();
                out.println("<div id="+rs[i].getRandevouz_id()+">");
                out.println("<p> Time:"+time+"  With : "+us.getUserName(rs[i].getUser_id())+"</p>");
                out.println("<button onclick=\"CancelRandevouz("+rs[i].getRandevouz_id()+")\">Cancel</button>\n");
                out.println("<button onclick=\"DoneRandevouz("+rs[i].getRandevouz_id()+")\">Done</button>\n");
                out.println("<br></div>\n");
                i++;
            }
            out.close();
//            String password = request.getParameter("password");
//            HttpSession session = request.getSession();
//            session.setAttribute("name", username);
//            session.setAttribute("pass", password);
//            EditSimpleUserTable tu = new EditSimpleUserTable();
//            SimpleUser us = tu.databaseToSimpleUser(username,password);
//            out.println(LoginData(us)+"<br>"+LoadDoctors()+"<br>"+LogoutButt());
//            out.close();
        }catch (SQLException ex) {
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
        //processRequest(request, response);
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
    
    
    String getUser(int id)throws SQLException, ClassNotFoundException{
        String result;
        EditSimpleUserTable us = new EditSimpleUserTable();
        result = us.getUserName(id);
        return result;
    }
}
