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
public class AddRandevouz extends HttpServlet {

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
        
         try(PrintWriter out = response.getWriter()){;
            
            String last = request.getParameter("lastnameR");
            String first = request.getParameter("firstnameR");
            String doctor_info = request.getParameter("doctor_infoR");
            String user_info = request.getParameter("user_infoR");
            int price = Integer.parseInt(request.getParameter("priceR"));
            String status = "free";
            String time = request.getParameter("time");
            String date = request.getParameter("date");
            time+=":00";
            String totalDate = date + " " + time ;
            
            EditSimpleUserTable us = new EditSimpleUserTable();
            
             String ts = date + " " + "7:59:00";
            String te = date+" "+"20:31:00";
            
            String[] arrOfStr = time.split(":", 3);
            int oh=Integer.parseInt(arrOfStr[0]);
            int om=Integer.parseInt(arrOfStr[1]);
            EditRandevouzTable tu = new EditRandevouzTable();
            Randevouz rs[] = tu.databaseToRandevouzTime(ts,te);
            int i=0;
            while(rs[i]!=null){
                String tm = rs[i].getDate_time();
                String[] splited = tm.split("\\s+");
                //System.out.println(splited[1]);
                
                tm = splited[1];
                arrOfStr = tm.split(":", 3);
                int h=Integer.parseInt(arrOfStr[0]);
                int m=Integer.parseInt(arrOfStr[1]);
//                System.out.println(h);
//                System.out.println(m);


                if((oh-h)>=2){
                    i++;
                    continue;
                }else if((h-oh)>=2){
                    i++;
                    continue;
                }else{
                
                    if(h>oh){
                    
                        m+=60;
                        if((m-om)<30){
                            response.setStatus(503);
                            return;
                        }
                        
                    }else if(h<oh){
                        int mt = om;
                        mt+=60;
                        if((mt-m)<30){
                            response.setStatus(503);
                            return;
                        }
                    }else{
                        if(((m-om)<30)&&((m-om)>0)){
                            response.setStatus(503);
                            return;    
                        }
                        if(((m-om) > -30)&&((m-om) < 0)){
                            response.setStatus(503);
                            return; 
                        }
                    
                    }
                
                }
                
                i++;
            }
            
            int uid = us.getUserId(first,last);
            if(uid == -1){
                response.setStatus(404);
                return;
            }
            HttpSession session = request.getSession();
            String name = (String)session.getAttribute("name");
            String pass = (String)session.getAttribute("pass");
            EditDoctorTable dt = new EditDoctorTable();
            Doctor d = dt.databaseToDoctor(name,pass);
            if(d == null){
                response.setStatus(404);
                return;
            }
            int did = d.getDoctor_id();
//            System.out.println(first);
//            System.out.println(last);
//            System.out.println(did);
//            System.out.println(uid);
//            System.out.println(totalDate);
            
            EditRandevouzTable rd = new EditRandevouzTable();
            
            String rj="";
            Randevouz r = new Randevouz();
            r.setDoctor_id(did);
            r.setUser_id(uid);
            r.setPrice(price);
            r.setDate_time(totalDate);
            r.setStatus(status);
            r.setDoctor_info(doctor_info);
            r.setUser_info(user_info);
            rd.createNewRandevouz(r);
            
            
            response.setStatus(200);
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
