<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>User Login and Registration xiaoxueqi</title>
</head>
<body>
<h1>User Login</h1>
<form method="post" action="UserLoginServlet">
	<label for="login-username">Username:</label>
	<input type="text" id="login-username" name="username" required><br>
	<label for="login-password">Password:</label>
	<input type="password" id="login-password" name="password" required><br>
	<input type="submit" value="Login">
</form>

<h1>User Registration</h1>
<form method="post" action="UserRegistrationServlet">
	<label for="register-userinfoid">UserInfoid:</label>
	<input type="text" id="register-userinfoid" name="userinfoid" required><br>
	<label for="register-username">Username:</label>
	<input type="text" id="register-username" name="username" required><br>
	<label for="register-password">Password:</label>
	<input type="password" id="register-password" name="password" required><br>
	<input type="submit" value="Register">
</form>

<h1>Change Password</h1>
<form method="post" action="ChangePasswordServlet">
	<label for="change-username">Username:</label>
	<input type="text" id="change-username" name="username" required><br>
	<label for="change-password-old">Old Password:</label>
	<input type="password" id="change-password-old" name="oldPassword" required><br>
	<label for="change-password-new">New Password:</label>
	<input type="password" id="change-password-new" name="newPassword" required><br>
	<input type="submit" value="Change Password">
</form>
</body>
</html>