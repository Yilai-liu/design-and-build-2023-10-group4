package main.java.testWeb.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import main.java.testWeb.vo.UserInfo;
import main.java.testWeb.dao.UserDAO;
import main.java.testWeb.dao.impl.UserDAOImpl;

public class ChangePasswordServlet extends HttpServlet {
    protected void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException {
        String username = req.getParameter("username");
        String oldPassword = req.getParameter("oldPassword");
        String newPassword = req.getParameter("newPassword");

        UserDAO dao = new UserDAOImpl();
        UserInfo userinfo = new UserInfo();
        userinfo.setUsername(username);
        userinfo.setPassword(oldPassword);

        try {
            int flag = dao.queryByUserInfo(userinfo);

            if (flag == 1) {
                userinfo.setNewPassword(newPassword);
                dao.changePassword(userinfo, newPassword);

                res.sendRedirect("./ChangeOk.jsp");
            } else {
                res.sendRedirect("./error.jsp");
            }
        } catch (Exception e) {
            e.printStackTrace();
            res.sendRedirect("./error.jsp");
        }
    }
}