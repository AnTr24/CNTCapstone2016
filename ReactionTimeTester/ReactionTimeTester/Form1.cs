using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Data.SqlClient;
using System.Configuration;

// Driver Main Form:    Provides user login/sign up options. Serial port configuration will create a config form.
// Author:              YunJie Li
// Date:                November 2016
namespace ReactionTimeTester
{
  // Delegate 
  delegate void ReadDataCallback(string text);

  public partial class Form_Main : Form
  {
    // Connection string to SQL database
    private string connString = "Data Source=[DSource];Initial Catalog=[Capstone2016];Persist Security Info=True;User ID=[user];Password=[Password]";

    SqlConnection sqlConn = null;   // SQL connection object used to insert data
    SqlCommand sqlCmd = null;       // SQL command used by the stored procedures

    List<byte> rxBuff = null;       // Buffer used to store serial data. Data will be parsed from here into floats
    string username = null;         // Username of the current login user
    bool IsLogin = false;           // Login status

    public Form_Main()
    {
      InitializeComponent();
    }

    private void Form_Main_Load(object sender, EventArgs e)
    {
      // Initialize the buffer
      rxBuff = new List<byte>();

      // Initialize the SQL connection
      sqlConn = new SqlConnection(connString);
      sqlConn.Open();
    }

    private void _btnConfig_Click(object sender, EventArgs e)
    {
      // Clear status label
      _lblStatus.Text = "";

      // Initialize the config form and set the properties
      Form_Config FormConfig = new Form_Config();
      FormConfig.PortName = _sPort.PortName;
      FormConfig.BaudRate = _sPort.BaudRate;
      FormConfig.DataBits = _sPort.DataBits;
      FormConfig.StopBits = _sPort.StopBits;
      FormConfig.Handshake = _sPort.Handshake;
      FormConfig.Parity = _sPort.Parity;

      // Use modal dialog and if OK return the properties
      if (DialogResult.OK == FormConfig.ShowDialog())
      {
        _sPort.PortName = FormConfig.PortName;
        _sPort.BaudRate = FormConfig.BaudRate;
        _sPort.DataBits = FormConfig.DataBits;
        _sPort.StopBits = FormConfig.StopBits;
        _sPort.Handshake = FormConfig.Handshake;
        _sPort.Parity = FormConfig.Parity;

        _lblStatus.ForeColor = Color.Green;
        _lblStatus.Text = "Config successful.";
      }
    }

    // Connect button handler
    private void _btnConn_Click(object sender, EventArgs e)
    {
      // If port is open
      if (_sPort.IsOpen)
      {
        _sPort.Close();
        _tmr_Main.Stop();
        _btnConfig.Enabled = true;
        _lblStatus.ForeColor = Color.Red;
        _lblStatus.Text = "Disconnected.";
        _btnConn.Text = "Connect";
      }
      // If port is closed
      else
      {
        try
        {
          _sPort.Encoding = Encoding.UTF8;
          _sPort.Open();
          _sPort.DiscardInBuffer();
          _tmr_Main.Start();

          _btnConfig.Enabled = false;
          _lblStatus.ForeColor = Color.Green;
          _lblStatus.Text = "Connected.";
          _btnConn.Text = "Disconnect";

        }
        catch (Exception err)
        {
          Console.WriteLine("Error opening the serial port: " + err.Message);
        }
      }
    }

    private void _btnLogin_Click(object sender, EventArgs e)
    {
      if (IsLogin)
      {
        _btnLogin.Text = "Login";
        IsLogin = false;
        _btnConn.Enabled = false;
        _btnSignup.Enabled = true;
        username = "";
        _lblStatus.Text = "You have logged out.";
        _tbxPwd.Enabled = true;
        _tbxCnfmPwd.Enabled = true;
        _tbxUsrn.Clear();
        _tbxPwd.Clear();
        _tbxCnfmPwd.Clear();
        return;
      }

      // Check if user has entered a username and password
      if (_tbxUsrn.Text == "" || _tbxPwd.Text == "")
      {
        _lblStatus.ForeColor = Color.Red;
        _lblStatus.Text = "Please enter your username and password.";
      }
      else
      {
        string usrN = _tbxUsrn.Text;
        string pswd = _tbxPwd.Text;

        sqlCmd = new SqlCommand();
        sqlCmd.Connection = sqlConn;

        sqlCmd.CommandType = CommandType.StoredProcedure;
        sqlCmd.CommandText = "ValidateUser";

        SqlParameter param = new SqlParameter();
        param.Direction = ParameterDirection.Input;
        param.ParameterName = "@username";
        param.SqlDbType = SqlDbType.NVarChar;
        param.Value = usrN;
        sqlCmd.Parameters.Add(param);

        param = new SqlParameter();
        param.Direction = ParameterDirection.Input;
        param.ParameterName = "@password";
        param.SqlDbType = SqlDbType.NVarChar;
        param.Value = pswd;
        sqlCmd.Parameters.Add(param);

        SqlParameter retVal = new SqlParameter();
        retVal.Direction = ParameterDirection.ReturnValue;
        retVal.ParameterName = "@return";
        retVal.SqlDbType = SqlDbType.Int;
        sqlCmd.Parameters.Add(retVal);

        try
        {
          sqlCmd.ExecuteNonQuery();

          if ((int)sqlCmd.Parameters["@return"].Value == 0)
          {
            username = usrN;
            _btnLogin.Text = "Logout";
            _lblStatus.ForeColor = Color.Green;
            _lblStatus.Text = "You have successfully logged in.";
            _btnConn.Enabled = true;
            _btnSignup.Enabled = false;
            IsLogin = true;
            _tbxPwd.Enabled = false;
            _tbxCnfmPwd.Enabled = false;
          }
          else if ((int)sqlCmd.Parameters["@return"].Value == 1)
          {
            _lblStatus.ForeColor = Color.Red;
            _lblStatus.Text = "The username or password is incorrect.";
          }
          else
            Console.WriteLine("Error. Please try again later.");
        }
        catch (Exception err)
        {
          Console.WriteLine("Error adding user: " + err.Message);
        }
      }
    }

    private void _btnSignup_Click(object sender, EventArgs e)
    {

      // Check if user has entered a username and password
      if (_tbxUsrn.Text == "" || _tbxPwd.Text == "")
      {
        _lblStatus.ForeColor = Color.Red;
        _lblStatus.Text = "Please enter your username and password.";
      }
      else if (_tbxPwd.Text != _tbxCnfmPwd.Text)
      {
        _lblStatus.ForeColor = Color.Red;
        _lblStatus.Text = "Password do not match. Please enter again.";
      }
      else
      {
        string usrN = _tbxUsrn.Text;
        string pswd = _tbxPwd.Text;

        sqlCmd = new SqlCommand();
        sqlCmd.Connection = sqlConn;

        sqlCmd.CommandType = CommandType.StoredProcedure;
        sqlCmd.CommandText = "AddUser";

        SqlParameter param = new SqlParameter();
        param.Direction = ParameterDirection.Input;
        param.ParameterName = "@username";
        param.SqlDbType = SqlDbType.NVarChar;
        param.Value = usrN;
        sqlCmd.Parameters.Add(param);

        param = new SqlParameter();
        param.Direction = ParameterDirection.Input;
        param.ParameterName = "@password";
        param.SqlDbType = SqlDbType.NVarChar;
        param.Value = pswd;
        sqlCmd.Parameters.Add(param);

        SqlParameter retVal = new SqlParameter();
        retVal.Direction = ParameterDirection.ReturnValue;
        retVal.ParameterName = "@return";
        retVal.SqlDbType = SqlDbType.Int;
        sqlCmd.Parameters.Add(retVal);

        try
        {
          sqlCmd.ExecuteNonQuery();

          if ((int)sqlCmd.Parameters["@return"].Value == 0)
          {
            username = usrN;
            _lblStatus.ForeColor = Color.Green;
            _lblStatus.Text = "You have successfully signed up.";
            IsLogin = true;
            _btnConn.Enabled = true;
            _btnSignup.Enabled = false;
            _btnLogin.Enabled = true;
            _btnLogin.Text = "Logout";
          }
          else if ((int)sqlCmd.Parameters["@return"].Value == 1)
          {
            _lblStatus.ForeColor = Color.Red;
            _lblStatus.Text = "The username has been taken.";
          }
          else
            Console.WriteLine("Error. Please try again later.");
        }
        catch (Exception err)
        {
          Console.WriteLine("Error adding user: " + err.Message);
        }
      }
    }

    // Call back method to insert serial data into database
    private void InsertData(string usrN, double rs1, double rs2, double rs3, double avg)
    {
      // Connect with sql using the connecting string
      sqlCmd = new SqlCommand();
      sqlCmd.Connection = sqlConn;

      sqlCmd.CommandType = CommandType.StoredProcedure;
      sqlCmd.CommandText = "AddTestResults";

      // Assign username
      SqlParameter param = new SqlParameter();
      param.Direction = ParameterDirection.Input;
      param.ParameterName = "@username";
      param.SqlDbType = SqlDbType.NVarChar;
      param.Value = usrN;
      sqlCmd.Parameters.Add(param);

      // Assign result 1
      param = new SqlParameter();
      param.Direction = ParameterDirection.Input;
      param.ParameterName = "@Test1Time";
      param.SqlDbType = SqlDbType.Float;
      param.Value = rs1;
      sqlCmd.Parameters.Add(param);

      // Assign result 2
      param = new SqlParameter();
      param.Direction = ParameterDirection.Input;
      param.ParameterName = "@Test2Time";
      param.SqlDbType = SqlDbType.Float;
      param.Value = rs2;
      sqlCmd.Parameters.Add(param);

      // Assign result 3
      param = new SqlParameter();
      param.Direction = ParameterDirection.Input;
      param.ParameterName = "@Test3Time";
      param.SqlDbType = SqlDbType.Float;
      param.Value = rs3;
      sqlCmd.Parameters.Add(param);

      // Assign results' average
      param = new SqlParameter();
      param.Direction = ParameterDirection.Input;
      param.ParameterName = "@TestAverage";
      param.SqlDbType = SqlDbType.Float;
      param.Value = avg;
      sqlCmd.Parameters.Add(param);

      try
      {
        sqlCmd.ExecuteNonQuery();
      }
      catch (Exception err)
      {
        Console.WriteLine("Error: " + err.Message);
      }

    }

    private void TestInsert(string s)
    {
      // Connect with sql using the connecting string
      sqlCmd = new SqlCommand();
      sqlCmd.Connection = sqlConn;

      sqlCmd.CommandType = CommandType.StoredProcedure;
      sqlCmd.CommandText = "TestProcedure";

      // Assign username
      SqlParameter param = new SqlParameter();
      param.Direction = ParameterDirection.Input;
      param.ParameterName = "@teststring";
      param.SqlDbType = SqlDbType.NVarChar;
      param.Value = s;
      sqlCmd.Parameters.Add(param);

      try
      {
        sqlCmd.ExecuteNonQuery();
      }
      catch (Exception err)
      {
        Console.WriteLine("Error: " + err.Message);
      }

    }


    private void _tmr_Main_Tick(object sender, EventArgs e)
    {
      try
      {
        // If nothing to read
        if (_sPort.BytesToRead == 0)
          return;

        // Read bytes from serial port until we have at least 17 bytes
        while (_sPort.IsOpen && _sPort.BytesToRead > 0 && rxBuff.Count < 17)
          rxBuff.Add((byte)_sPort.ReadByte());

        // Once we have 9 bytes, we can start to parse
        if (rxBuff.Count >= 17 &&
            (rxBuff[0] != 126 || rxBuff[2] != 46 || rxBuff[7] != 46 || rxBuff[12] != 46 || rxBuff[16] != 33))
        {
          rxBuff.RemoveAt(0);
          return;
        }
        else if (rxBuff.Count < 17)
          return;


        ASCIIEncoding encoding = new ASCIIEncoding();

        // Parse the data and insert into the database
        double rs1 = double.Parse(encoding.GetString(rxBuff.GetRange(1, 5).ToArray()));
        double rs2 = double.Parse(encoding.GetString(rxBuff.GetRange(6, 5).ToArray()));
        double rs3 = double.Parse(encoding.GetString(rxBuff.GetRange(11, 5).ToArray()));
        double avg = (rs1 + rs2 + rs3) / 3;

        string s = rs1 + " " + rs2 + " " + rs3 + " " + avg;
        Console.WriteLine(s);

        // Remove the whole frame
        for (int i = 0; i < 17; i++)
          rxBuff.RemoveAt(0);

        InsertData(username, rs1, rs2, rs3, avg);
      }
      catch (Exception err)
      {
        Console.WriteLine("Error reading data from serial port: " + err.Message);
      }




    }





  }
}

