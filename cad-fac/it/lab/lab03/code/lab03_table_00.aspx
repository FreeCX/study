<%@ Page Language="C#" AutoEventWireup="true" CodeFile="table_00.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <p>Общая таблица</p>
        <table id="TableViewRegister" runat="server">
            <tr>
                <th>Подразделение</th>
                <th>Инструмент</th>
                <th>Ответственный</th>
                <th>Изготовитель</th>
                <th>Страна</th>
                <th>Обуродование</th>
                <th>Количество</th>
            </tr>
        </table>
        <div>
            <br>Страница для перехода:<br>
            <asp:Button ID="page_button_00" runat="server" Width="50px" Text="00" OnCommand="button_click" CommandArgument="0" />
            <asp:Button ID="page_button_01" runat="server" Width="50px" Text="01" OnCommand="button_click" CommandArgument="1" />
            <asp:Button ID="page_button_02" runat="server" Width="50px" Text="02" OnCommand="button_click" CommandArgument="2" />
            <asp:Button ID="page_button_03" runat="server" Width="50px" Text="03" OnCommand="button_click" CommandArgument="3" />
            <asp:Button ID="page_button_04" runat="server" Width="50px" Text="04" OnCommand="button_click" CommandArgument="4" />
            <asp:Button ID="page_button_05" runat="server" Width="50px" Text="05" OnCommand="button_click" CommandArgument="5" />
            <asp:Button ID="page_button_06" runat="server" Width="50px" Text="06" OnCommand="button_click" CommandArgument="6" />
            <asp:Button ID="page_button_07" runat="server" Width="50px" Text="07" OnCommand="button_click" CommandArgument="7" />
        </div>
    </div>
        <asp:SqlDataSource ID="dsRegister" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString %>" DataSourceMode="DataReader" SelectCommand="SELECT tbDepartments.vc_name AS DepName, tbDepartments.i_id_department AS id_dep_d, tbLists.i_id_list AS id_list_l, tbLists.i_id_tool AS id_tool_l, tbLists.i_count AS Count_l, tbManufactured.i_id_manuf AS id_manuf_m, tbManufactured.vc_name AS ManufName, tbManufactured.vc_country AS CouName, tbMarks.i_id_mark AS id_mark_m, tbMarks.vc_name AS MarkName, tbPersonList.i_id_personlist AS id_personlist_pl, tbPersonList.i_id_person AS id_person_pl, tbPersonList.i_id_tool AS id_tool_pl, tbPersonList.i_count AS Count_pl, tbPersons.i_id_person AS id_person_p, tbPersons.vc_name AS PersName, tbTools.vc_name AS ToolName, tbTools.i_id_manuf AS id_manuf_t, tbTools.i_id_mark AS id_mark_t, tbTools.i_id_tool AS id_tool_t, tbLists.i_id_department AS id_dep_l FROM tbMarks INNER JOIN tbDepartments INNER JOIN tbLists ON tbDepartments.i_id_department = tbLists.i_id_department INNER JOIN tbPersons INNER JOIN tbPersonList ON tbPersons.i_id_person = tbPersonList.i_id_person INNER JOIN tbTools ON tbPersonList.i_id_tool = tbTools.i_id_tool ON tbLists.i_id_tool = tbTools.i_id_tool INNER JOIN tbManufactured ON tbTools.i_id_manuf = tbManufactured.i_id_manuf ON tbMarks.i_id_mark = tbTools.i_id_mark">
        </asp:SqlDataSource>
    </form>
</body>
</html>
