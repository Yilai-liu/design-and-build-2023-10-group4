package main.java.testWeb.vo;

public class UserInfo {

    private String userinfoid;
    private String username;
    private String password;
    private String newPassword;


    public String getUserinfoid() {return userinfoid;}

    public void setUserInfoid(String userinfoid) {
        this.userinfoid = userinfoid;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }


    public String getNewPassword() {
        return newPassword;
    }

    public void setNewPassword(String newPassword) {
        this.newPassword = newPassword;
    }
}