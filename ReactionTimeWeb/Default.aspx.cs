using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
  protected void Page_Load(object sender, EventArgs e)
  {

  }

  protected void _gvResults_SelectedIndexChanged(object sender, EventArgs e)
  {
    string usrN = _gvResults.SelectedValue.ToString();

    _lblUsername.Text = usrN;
    _lblUsername.Font.Size = 18;
    _lblUsername.Font.Bold = true;
    _lblUsername.Font.Italic = true;
    _lblUsername.Font.Underline = true;

    using (SqlConnection conn = new SqlConnection(ConfigurationManager.ConnectionStrings["CapstoneCS"].ConnectionString))
    {
      conn.Open();
      using (SqlCommand cmd = new SqlCommand())
      {
        // Get total average
        cmd.Connection = conn;
        cmd.CommandType = System.Data.CommandType.StoredProcedure;
        cmd.CommandText = "GetUserAvgTime";

        SqlParameter param = new SqlParameter();
        param.Direction = System.Data.ParameterDirection.Input;
        param.SqlDbType = System.Data.SqlDbType.NVarChar;
        param.ParameterName = "@username";
        param.Value = usrN;

        cmd.Parameters.Add(param);

        SqlDataReader reader = cmd.ExecuteReader();
        if (!reader.HasRows)
          return;

        reader.Read();
        _lblStats.Text = "Total Average: " + string.Format("{0:F3}", reader[0]);

        // Get fastest result
        //cmd.CommandText = "GetUserFastestTime";

        //reader = cmd.ExecuteReader();
        //if (!reader.HasRows)
        //  return;

        //reader.Read();
        //_lblStats.Text += "Fastest Reaction: " + string.Format("{0:F3}", reader[0]);
      }
    }
  }
}