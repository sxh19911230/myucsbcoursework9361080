import java.sql.*;
import java.io.*;


/**
 * A class to hold the configuration information for a particular database
 */
class Config{
	public static String host = "localhost";
	public static String username = "myUser";
	public static String password = "myPass";
	public static String database = "project";
}

public class mysqlcmd {
	
	public static java.sql.Connection conn;

	public static Statement stmt;
	public static ResultSet rs;
	public static PreparedStatement pstmt;
	public static InputStream inputStream;
	public static OutputStream outputStream;
	public static File file;
	public static Blob salaryBin;
	public static String [] encrypt = {"./enc", null, "tmp"};
	public static String [] decrypt = {"./dec", "tmp"};

	// A static initialization for all the static variables
	public static void main(String[] args){

        connect(args);
		
		startCmd();
		
    }

	/**
	 * For Connection
	 */
	public static void connect(String[] args){
		
		int i = 0;
		boolean setPwd = false;
		
		while (i < args.length) {
			if (args[i].equals("-u")) Config.username = args[++i];
			else if (args[i].equals("-h")) Config.host = args[++i];
			else if (args[i].equals("-p")) setPwd = true;
			++i;
		}
		
		if (setPwd) {
			System.out.print("Password: ");
			Config.password = new String(System.console().readPassword());
		}
		try {
		    Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
		    throw new RuntimeException("Cannot find the driver in the classpath!", e);
		}
		try {
			conn = java.sql.DriverManager.getConnection("jdbc:mysql://"
			    		   + Config.host+"/"+ Config.database,
			    		   Config.username, Config.password);
			
		} catch (SQLException e) {
			System.out.println("Fail to establish connection");
			System.exit(1);
		}
	}
	public static void startCmd (){
		
		java.util.Scanner s = new java.util.Scanner(System.in);
		String input;
		
		System.out.print("myspl-> ");
		input = s.nextLine();
		
		while (!input.equals("quit") && !input.equals("exit")) {
			try {
				sendAndRecv(input);
			} catch (Exception e) {
				System.out.println("Error: " + e.getMessage());
			}
			System.out.print("myspl-> ");
			input = s.nextLine();
		}
	}

	
	public static void sendAndRecv(String input) throws Exception {
		
		String [] tokens = input.split(" ");
		String myStatement;

		if (tokens[0].toUpperCase().equals("INSERT")) {
			
			if (tokens.length != 4) throw new Exception("Insertion Statement Format Mismatch\n");
			
			encrypt[1] = tokens[3];
			Runtime.getRuntime().exec(encrypt).waitFor();
			file = new File("tmp");
			inputStream = new FileInputStream(file);
			pstmt = conn.prepareStatement(String.format("INSERT INTO employees VALUES(%s,%s,?);",tokens[1],tokens[2]));
			pstmt.setBlob(1, inputStream);
			pstmt.executeUpdate();
			file.delete();
		} else if (tokens[0].toUpperCase().equals("SELECT")) {
			if (tokens[1].equals("*")) {
				if (tokens.length != 2) throw new Exception("Query Statement Format Mismatch\n");
				stmt = conn.createStatement();
				rs = stmt.executeQuery("SELECT * FROM employees;");
				printRS();
			} else if (tokens[1].matches("^\\d+$")) {
				if (tokens.length != 2) throw new Exception("Query Statement Format Mismatch\n");
				stmt = conn.createStatement();
				rs = stmt.executeQuery("SELECT * FROM employees WHERE id = " + tokens[1] +";");
				printRS();
			} else if (tokens[1].equals("SUM")) {
				myStatement = makeupStatement(tokens);
				stmt = conn.createStatement();
				rs = stmt.executeQuery(myStatement);
				printRS();
			} else if (tokens[1].equals("AVG")){
				myStatement = makeupStatement(tokens);
				stmt = conn.createStatement();
				rs = stmt.executeQuery(myStatement);
				printRSAVE();
			} else {
				throw new Exception("Query Statement Format Mismatch\n");
			}
		} else if (!tokens[0].equals("")) {
			System.out.println("Unknown command...");
		}
	}
	
	public static void printRS() throws Exception {
		ResultSetMetaData rsmd = rs.getMetaData();
		int blobPosition = -1;
		int columnCount = rsmd.getColumnCount();
		String tmp;
		
		
		for (int i = 0; i < columnCount; ++i) {
			tmp = rsmd.getColumnName(i+1);
			if (tmp.equals("SUM_HE(salary)")) {
				System.out.print("SUM\t");
				blobPosition=i;
			} else {
				if (tmp.equals("salary")) {
					blobPosition=i;
				}
				System.out.print(tmp + '\t');
			}
		}
		System.out.println();
		
		while (rs.next()) {
			
			for (int i = 0; i < columnCount; ++i) {
				if (i == blobPosition) {
					salaryBin = rs.getBlob(i+1);
					inputStream = salaryBin.getBinaryStream();
					file = new File("tmp");
					
					outputStream = new FileOutputStream(file);
					
					byte[] buff = new byte[20];
					inputStream.read(buff);
					outputStream.write(buff, 0, 16);
					outputStream.close();
					Process p = Runtime.getRuntime().exec(decrypt);
					p.waitFor();
					String salary = new BufferedReader(new InputStreamReader(p.getInputStream())).readLine();
					System.out.print(salary + '\t');
					
					file.delete();
				} else {
					System.out.print(rs.getString(i+ 1) + '\t');
				}
			}
			System.out.println();
		}
	}
	
	public static String makeupStatement(String[] tokens) throws Exception {
		int i = 2;
		StringBuilder sb = new StringBuilder("SELECT SUM_HE(salary) FROM employees ");
		if (i < tokens.length && tokens[i].toUpperCase().equals("WHERE")){
			while (i < tokens.length && !tokens[i].toUpperCase().equals("GROUP") && !tokens[i].toUpperCase().equals("HAVING")) {
				sb.append(tokens[i]);
				sb.append(' ');
				i++;
			}
		}
		if (i < tokens.length && tokens[i].toUpperCase().equals("GROUP")){
			if (++i < tokens.length && tokens[i].toUpperCase().equals("BY") && ++i < tokens.length && tokens[i].toUpperCase().equals("AGE")) {
				++i;
				sb.insert(7, "age, ");
				sb.append("GROUP BY age ");
			} else {
				throw new Exception("Query Statement Format Mismatch1\n");
			}
		}
		if (i < tokens.length && tokens[i].toUpperCase().equals("HAVING")){
			while (i < tokens.length) {
				sb.append(tokens[i]);
				sb.append(' ');
				i++;
			}
		}
		sb.append(';');
		
		if (i < tokens.length) {
			throw new Exception("Query Statement Format Mismatch2\n");
		}
		
		if (tokens[1].equals("AVG")) {
			sb.insert(7, "COUNT(*), ");
		}

		return sb.toString();
		
	}
	
	public static void printRSAVE() throws Exception {
		ResultSetMetaData rsmd = rs.getMetaData();
		int blobPosition = -1;
		int columnCount = rsmd.getColumnCount();
		int n;
		String tmp;
		
		
		for (int i = 1; i < columnCount; ++i) {
			tmp = rsmd.getColumnName(i+1);
			if (tmp.equals("SUM_HE(salary)")) {
				System.out.print("AVE\t");
				blobPosition=i;
			} else {
				if (tmp.equals("salary")) {
					blobPosition=i;
				}
				System.out.print(tmp + '\t');
			}
		}
		System.out.println();
		
		while (rs.next()) {
			
			for (int i = 1; i < columnCount; ++i) {
				if (i == blobPosition) {
					n = rs.getInt(1);
					salaryBin = rs.getBlob(i+1);
					inputStream = salaryBin.getBinaryStream();
					file = new File("tmp");
					
					outputStream = new FileOutputStream(file);
					
					byte[] buff = new byte[20];
					inputStream.read(buff);
					outputStream.write(buff, 0, 16);
					outputStream.close();
					Process p = Runtime.getRuntime().exec(decrypt);
					p.waitFor();
					String salary = new BufferedReader(new InputStreamReader(p.getInputStream())).readLine();
					
					System.out.print("" + (Integer.parseInt(salary) / n) + '\t');
					
					file.delete();
				} else {
					System.out.print(rs.getString(i+ 1) + '\t');
				}
			}
			System.out.println();
		}
	}
}




