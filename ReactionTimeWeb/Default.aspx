<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
  <title>NAIT Capstone - Reaction Time Results</title>
  <meta charset="utf-8" />
  <meta http-equiv="X-UA-Compatible" content="IE=edge" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <link href="StyleSheet.css" rel="stylesheet" type="text/css" />
  <script src="//ajax.googleapis.com/ajax/libs/jquery/2.1.0/jquery.min.js"></script>
</head>
<body>
  <form id="form1" runat="server">
    <div class="jumbotron">
      <h1 class="text-center">Reaction Time Results</h1>
    </div>
    <div class="container">
      <asp:Label ID="_lblSearch" runat="server" Text="Search User: "></asp:Label>
      <asp:TextBox ID="_tbxSearch" runat="server"></asp:TextBox>
      <asp:SqlDataSource ID="_sdsResults" runat="server" ConnectionString="<%$ ConnectionStrings:CapstoneCS %>" SelectCommand="GetAllResults" SelectCommandType="StoredProcedure">
        <SelectParameters>
          <asp:ControlParameter ControlID="_tbxSearch" Name="searchFilter" PropertyName="Text" Type="String" ConvertEmptyStringToNull="False" />
        </SelectParameters>
      </asp:SqlDataSource>
      <asp:GridView ID="_gvResults" runat="server" Width="100%" AutoGenerateColumns="False" BackColor="LightGoldenrodYellow" BorderColor="Tan" BorderWidth="1px" CellPadding="2" DataSourceID="_sdsResults" ForeColor="Black" GridLines="None" AllowPaging="True" AllowSorting="True" DataKeyNames="Username" OnSelectedIndexChanged="_gvResults_SelectedIndexChanged">
        <AlternatingRowStyle BackColor="PaleGoldenrod" />
        <Columns>
          <asp:ButtonField CommandName="Select" DataTextField="Username" HeaderText="Username" SortExpression="Username" Text="Button" />
          <asp:BoundField DataField="Test1" HeaderText="Test #1" SortExpression="Test1" DataFormatString="{0:F3}" />
          <asp:BoundField DataField="Test2" HeaderText="Test #2" SortExpression="Test2" DataFormatString="{0:F3}" />
          <asp:BoundField DataField="Test3" HeaderText="Test #3" SortExpression="Test3" DataFormatString="{0:F3}" />
          <asp:BoundField DataField="Average" HeaderText="Average" SortExpression="Average" DataFormatString="{0:F3}" />
          <asp:BoundField DataField="Date Taken" HeaderText="Date Taken" SortExpression="Date Taken" DataFormatString="{0:MMM dd, yyyy hh:mm:ss}" />
        </Columns>
        <FooterStyle BackColor="Tan" />
        <HeaderStyle BackColor="Tan" Font-Bold="True" />
        <PagerStyle BackColor="PaleGoldenrod" ForeColor="DarkSlateBlue" HorizontalAlign="Center" />
        <SelectedRowStyle BackColor="DarkSlateBlue" ForeColor="GhostWhite" />
        <SortedAscendingCellStyle BackColor="#FAFAE7" />
        <SortedAscendingHeaderStyle BackColor="#DAC09E" />
        <SortedDescendingCellStyle BackColor="#E1DB9C" />
        <SortedDescendingHeaderStyle BackColor="#C2A47B" />
      </asp:GridView>
    </div>
    <div class="container">
      <asp:Label ID="_lblUsername" runat="server" Text="Please pick a username to see the history statistics."></asp:Label>
      <asp:Label ID="_lblStats" runat="server"></asp:Label>
      <asp:SqlDataSource ID="_sdsUserHistory" runat="server" ConnectionString="<%$ ConnectionStrings:CapstoneCS %>" SelectCommand="GetUserTestHistory" SelectCommandType="StoredProcedure">
        <SelectParameters>
          <asp:ControlParameter ControlID="_gvResults" Name="username" PropertyName="SelectedValue" Type="String" />
        </SelectParameters>
      </asp:SqlDataSource>
      <asp:GridView ID="_gvUserHistory" runat="server" Width="100%" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False" BackColor="White" BorderColor="#999999" BorderStyle="Solid" BorderWidth="1px" CellPadding="3" DataSourceID="_sdsUserHistory" ForeColor="Black" GridLines="Vertical">
        <AlternatingRowStyle BackColor="#CCCCCC" />
        <Columns>
          <asp:BoundField DataField="Test1" DataFormatString="{0:F3}" HeaderText="Test #1" SortExpression="Test1" />
          <asp:BoundField DataField="Test2" DataFormatString="{0:F3}" HeaderText="Test #2" SortExpression="Test2" />
          <asp:BoundField DataField="Test3" DataFormatString="{0:F3}" HeaderText="Test #3" SortExpression="Test3" />
          <asp:BoundField DataField="Average" DataFormatString="{0:F3}" HeaderText="Average" SortExpression="Average" />
          <asp:BoundField DataField="Date Taken" DataFormatString="{0:MMM dd, yyyy hh:mm:ss}" HeaderText="Date Taken" SortExpression="Date Taken" />
        </Columns>
        <FooterStyle BackColor="#CCCCCC" />
        <HeaderStyle BackColor="Black" Font-Bold="True" ForeColor="White" />
        <PagerStyle BackColor="#999999" ForeColor="Black" HorizontalAlign="Center" />
        <SelectedRowStyle BackColor="#000099" Font-Bold="True" ForeColor="White" />
        <SortedAscendingCellStyle BackColor="#F1F1F1" />
        <SortedAscendingHeaderStyle BackColor="#808080" />
        <SortedDescendingCellStyle BackColor="#CAC9C9" />
        <SortedDescendingHeaderStyle BackColor="#383838" />
      </asp:GridView>
    </div>
    <div class="container-fluid footer text-center">
      © Copyright 2016 by Andy Tran & YunJie Li
    </div>
  </form>
</body>
</html>
