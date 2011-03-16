package org.gadek.Leroy;

import java.sql.*;

public class MySQLAccess {
	
	private Connection connect = null;
	private Statement statement = null;
	private PreparedStatement preparedStatement = null;
	private ResultSet resultSet = null;
	
	public void readDB() {
		try {
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			connect = DriverManager.getConnection("jdbc:mysql://localhost:3306/Leroy?user=leroy&password=leroy");
			
			//statement = connect.createStatement();
			//resultSet = statement.executeQuery("select * from Leroy.users");
			//writeResultSet(resultSet);
			
			preparedStatement = connect.prepareStatement("insert into Leroy.users(name) values (?)");
			preparedStatement.setString(1, "Konrad");
			preparedStatement.executeUpdate();
			
			preparedStatement = connect.prepareStatement("select name from Leroy.users");
			resultSet = preparedStatement.executeQuery();
			writeResultSet(resultSet);
			
			writeMD(resultSet);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			close();
		}
	}

	private void close() {
		try {
			if(resultSet != null)
				resultSet.close();
			if(statement != null)
				statement.close();
			if(connect != null)
				connect.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writeMD(ResultSet resultSet) throws SQLException {
		System.out.println("Kolumny:");
		System.out.println("Table: " + resultSet.getMetaData().getTableName(1));
		for(int i=1; i<= resultSet.getMetaData().getColumnCount(); ++i)
			System.out.println("Column " + i + " = " + resultSet.getMetaData().getColumnName(i));
	}

	private void writeResultSet(ResultSet resultSet) throws SQLException {
		while(resultSet.next()) {
			String name = resultSet.getString("name");
			System.out.println("DB> name = " + name);
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		MySQLAccess blah = new MySQLAccess();
		blah.readDB();
	}

}
