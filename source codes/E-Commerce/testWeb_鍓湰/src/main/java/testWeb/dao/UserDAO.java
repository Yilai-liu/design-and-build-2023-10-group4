package main.java.testWeb.dao;

import main.java.testWeb.vo.UserInfo;

public interface UserDAO {
	int queryByUserInfo(UserInfo userinfo) throws Exception;
	void addUser(UserInfo userinfo) throws Exception;
	void changePassword(UserInfo userinfo, String newPassword) throws Exception;
}

