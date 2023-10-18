
package main.java.testWeb.db;

import java.sql.Connection;
import java.sql.DriverManager;

public class DBConnect {

    private final String DBDRIVER = "com.mysql.cj.jdbc.Driver";
    private final String DBURL = "jdbc:mysql://localhost:3306/JavaWebDB";//jdbc:mysql://localhost:3306/?user=root
    private final String DBUSER = "root";
    private final String DBPASSWORD = "Heych2003" ;
    private Connection conn = null ;

    public DBConnect() {
        try {
            Class.forName(DBDRIVER);
            this.conn = DriverManager.getConnection(DBURL, DBUSER, DBPASSWORD);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public Connection getConnection() {
        return this.conn;
    }

    public void close() {
        try {
            if (conn != null) {
                conn.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}