/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servlets;

import database.tables.EditBloodTestTable;
import database.tables.EditDoctorTable;
import database.tables.EditSimpleUserTable;
import java.util.*;
import java.io.IOException;
import java.io.PrintWriter;
import static java.lang.System.out;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import mainClasses.BloodTest;
import mainClasses.Doctor;
import mainClasses.SimpleUser;

/**
 *
 * @author GS
 */
public class GetDoctorsUser extends HttpServlet {

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
            double ulat = u.getLat();
            double ulon = u.getLon();
            String by = request.getParameter("by");
            System.out.println("ok");
            EditDoctorTable dt = new EditDoctorTable();
            ArrayList<Doctor> dl = dt.databaseToDoctors();
            if (by.equals("car")) {
                System.out.println("ok");
                String s = ulat + "&" + ulon + "+";
                int i;
                for (i = 0; i < dl.size(); i++) {
                    System.out.println("ok");
                    if (i != 0) {
                        s += "%3B";
                    }
                    double dlat = dl.get(i).getLat();
                    double dlon = dl.get(i).getLon();
                    s += dlat + "%2C" + dlon;

                }
                response.setStatus(403);
                out.println(s);
                out.close();

            } else {
                int i = 0;
                ArrayList< Double> dis = new ArrayList< Double>();
                for (i = 0; i < dl.size(); i++) {
                    double rd = distance(ulat, dl.get(i).getLat(), ulon, dl.get(i).getLon());
                    dis.add(rd);
                }

                for (i = 0; i < dis.size(); i++) {

                    for (int j = dis.size() - 1; j > i; j--) {
                        if (dis.get(i) > dis.get(j)) {

                            double tmp = dis.get(i);

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
                response.setStatus(200);
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

    public static double distance(double lat1, double lat2, double lon1, double lon2) {

        // The math module contains a function
        // named toRadians which converts from
        // degrees to radians.
        lon1 = Math.toRadians(lon1);
        lon2 = Math.toRadians(lon2);
        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        // Haversine formula
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = Math.pow(Math.sin(dlat / 2), 2)
                + Math.cos(lat1) * Math.cos(lat2)
                * Math.pow(Math.sin(dlon / 2), 2);

        double c = 2 * Math.asin(Math.sqrt(a));

        // Radius of earth in kilometers. Use 3956
        // for miles
        double r = 6371;

        // calculate the result
        return (c * r);
    }

}
