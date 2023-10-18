package main.java.testWeb.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import main.java.testWeb.vo.UserInfo;
import main.java.testWeb.dao.UserDAO;
import main.java.testWeb.dao.impl.UserDAOImpl;

public class UserRegistrationServlet extends HttpServlet {

    public void doPost(HttpServletRequest req, HttpServletResponse res)
            throws IOException, ServletException {
        UserInfo userinfo = new UserInfo();

        userinfo.setUserInfoid(req.getParameter("userinfoid"));
        userinfo.setUsername(req.getParameter("username"));
        userinfo.setPassword(req.getParameter("password"));

        UserDAO dao = new UserDAOImpl();

        try {
            dao.addUser(userinfo);

            HttpSession session = req.getSession();
            session.setAttribute("username", userinfo.getUsername());

            res.sendRedirect("./RegistrationOK.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            res.sendRedirect("./error.jsp");
        }
    }
}
