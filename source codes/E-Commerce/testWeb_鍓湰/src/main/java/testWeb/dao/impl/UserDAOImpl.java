package main.java.testWeb.dao.impl;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import main.java.testWeb.dao.UserDAO;
import main.java.testWeb.db.*;
import main.java.testWeb.vo.*;

public class UserDAOImpl implements UserDAO {
    private DBConnect dbc = null;

    public UserDAOImpl() {
        dbc = new DBConnect();
    }

    public int queryByUserInfo(UserInfo userinfo) throws Exception {
        int flag = 0;
        String sql = "SELECT * FROM userinfo WHERE username=?";
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            pstmt = dbc.getConnection().prepareStatement(sql);
            pstmt.setString(1, userinfo.getUsername());
            rs = pstmt.executeQuery();

            while (rs.next()) {
                if (rs.getString("password").equals(userinfo.getPassword())) {
                    flag = 1;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            if (rs != null) {
                rs.close();
            }
            if (pstmt != null) {
                pstmt.close();
            }
        }

        return flag;
    }

    public void addUser(UserInfo userinfo) throws Exception {
        String sql = "INSERT INTO userinfo (userinfoid, username, password) VALUES (?,?,?)";
        PreparedStatement pstmt = null;

        try {
            pstmt = dbc.getConnection().prepareStatement(sql);

            pstmt.setString(1, userinfo.getUserinfoid());
            pstmt.setString(2, userinfo.getUsername());
            pstmt.setString(3, userinfo.getPassword());

            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            if (pstmt != null) {
                pstmt.close();
            }
        }
    }

    public void changePassword(UserInfo userinfo, String newPassword) throws Exception {
        String sql = "UPDATE userinfo SET password=? WHERE username=?";
        PreparedStatement pstmt = null;

        try {
            pstmt = dbc.getConnection().prepareStatement(sql);
            pstmt.setString(1, newPassword);
            pstmt.setString(2, userinfo.getUsername());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            if (pstmt != null) {
                pstmt.close();
            }
        }
    }
}