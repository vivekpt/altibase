import Altibase.jdbc.driver.*;
import Altibase.jdbc.driver.ex.*;
import java.util.Properties;
import java.sql.*;
import java.io.*;

class  FailOverSampleSTF 
{

    public static void main(String args[])  throws Exception
    {
        //---------------------------------------------------
        // Initialization
        //---------------------------------------------------
        // AlternateServers�� ������ property�̴�.
        
       /* �̷��� ��� connection string�� �����ϱ� ������
       altibase_cli.ini���� Data Source section�� ����ϰ�,
       [DataSource�̸�] 
       AlternateServers=(128.1.3.53:20300,128.1.3.52:20301)
       .......................
       URL�� ������ ���� ����ϸ� �ȴ�.
       jdbc:Altibase://DataSource�̸�
       */
        String sURL = "jdbc:Altibase://127.0.0.1:" + args[0]+"/mydb?AlternateServers=(128.1.3.53:20300,128.1.3.52:20301)&ConnectionRetryCount=3&ConnectionRetryDelay=10&SessionFailOver=on";
        try
        {
            Class.forName("Altibase.jdbc.driver.AltibaseDriver");
        }
        catch ( Exception e )
        {
            System.err.println("Can't register Altibase Driver\n");
            return;
        }

        //---------------------------------------------------
        // Test Body
        //---------------------------------------------------

        //-----------------------
        // Preparation
        //-----------------------

        Properties sProp = new Properties();
        Connection sCon;
        PreparedStatement  sStmt = null;
        ResultSet sRes = null ;
        sProp.put("user", "SYS");
        sProp.put("password", "MANAGER");
        
        sCon = DriverManager.getConnection(sURL, sProp);
        // Session Fail-Over�� ���Ͽ� �������� �������� ���α׷����ؾ� �մϴ�.
        /*
          while (true)
          {
            try
            {
            
            }
            catch(  SQLException e)
            {
               //Fail-Over�� �߻�.
                if (e.getErrorCode() == ErrorDef.FAILOVER_SUCCESS)
                {
                    continue;
                }
                System.out.println( "EXCEPTION : " + e.getMessage() );
                break;

            }       
             break;
          } // while
        */
        while(true)
        {
            try 
            {
                sStmt = sCon.prepareStatement("SELECT C1 FROM T2   ORDER BY C1");
            	sRes = sStmt.executeQuery();
                while( sRes.next() )
                {
                    System.out.println( "VALUE : " + sRes.getString(1)  );
                }//while
            }
            
            catch ( SQLException e )
            {
                //FailOver�� �߻��Ͽ���.
                if (e.getErrorCode() == ErrorDef.FAILOVER_SUCCESS)
                {
                    continue;
                }
                System.out.println( "EXCEPTION : " + e.getMessage() );
                break;
            }
            break;

        }
        
        sRes.close();
        //---------------------------------------------------
        // Finalize
        //---------------------------------------------------
        
        sStmt.close();
        sCon.close();
    }
}