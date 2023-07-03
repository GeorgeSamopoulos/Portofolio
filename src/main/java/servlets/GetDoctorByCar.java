/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import database.tables.EditDoctorTable;
import database.tables.EditSimpleUserTable;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import mainClasses.Doctor;
import mainClasses.SimpleUser;
import static servlets.GetDoctorsUser.distance;

/**
 *
 * @author GS
 */
@WebServlet(name = "GetDoctorByCar", urlPatterns = {"/GetDoctorByCar"})
public class GetDoctorByCar extends HttpServlet {

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

            EditSimpleUserTable us = new EditSimpleUserTable();
            HttpSession session = request.getSession();
            String username = (String) session.getAttribute("name");
            String password = (String) session.getAttribute("pass");
            SimpleUser u = us.databaseToSimpleUser(username, password);
            
            ArrayList<Integer> dis = new ArrayList<Integer>();
            int i=0;
            boolean flag=true;
            while(flag){
                String temp = (String) session.getAttribute("dis"+i);
                if(temp==null){
                    flag=false;
                }else{
                    dis.add(Integer.parseInt(temp));
                }
                i++;
            }
            
            EditDoctorTable dt = new EditDoctorTable();
            ArrayList<Doctor> dl = dt.databaseToDoctors();
            for (i = 0; i < dis.size(); i++) {

                    for (int j = dis.size() - 1; j > i; j--) {
                        if (dis.get(i) > dis.get(j)) {

                            int tmp = dis.get(i);

                            dis.set(i, dis.get(j));
                            dis.set(j, tmp);
                            
                            Doctor dtemp = dl.get(i);
                            dl.set(i, dl.get(j));
                            dl.set(j, dtemp);

                        }

                    }

            }
            for (i = 0; i < dl.size(); i++) {
                     out.println("<div id=doc"+dl.get(i).getDoctor_id()+">");
                     out.println("<p>"+dl.get(i).getFirstname()+" "+dl.get(i).getLastname()+": </p>");
                     out.println("<button onclick=\"SelectDoctor("+dl.get(i).getDoctor_id()+")\">Select</button>\n");
                     out.println("</div><br>");
                 
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
