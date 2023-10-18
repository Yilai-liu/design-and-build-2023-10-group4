package main.java.testWeb.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import main.java.testWeb.vo.UserInfo;
import main.java.testWeb.dao.UserDAO;
import main.java.testWeb.dao.impl.*;

public class UserLoginServlet extends HttpServlet {

	public void doGet(HttpServletRequest req, HttpServletResponse res)
			throws IOException, ServletException{
	}

	public void doPost(HttpServletRequest req, HttpServletResponse res)
			throws IOException, ServletException{
		UserInfo userinfo = new UserInfo();
		userinfo.setUsername(req.getParameter("username"));
		userinfo.setPassword(req.getParameter("password"));
		//这里把两个数据封装在了一个值对象之中，非常方便
		UserDAO dao = new UserDAOImpl();
		int flag = 0;
		try {
			flag = dao.queryByUserInfo(userinfo);
			if(flag == 1){
				HttpSession session=req.getSession();
				session.setAttribute("username", userinfo.getUsername());

				res.getWriter().println("<h1>Hello</h1>");
//           res.sendRedirect("./welcome.jsp");
			} else {
				res.sendRedirect("./error.jsp");
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}