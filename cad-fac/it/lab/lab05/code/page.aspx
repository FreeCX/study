<asp:GridView ID="GridView1" runat="server" 
    AutoGenerateColumns="False" DataKeyNames="i_id_personlist" DataSourceID="dsList">
    <Columns>
        <asp:BoundField DataField="i_id_person" 
            HeaderText="i_id_person" 
            SortExpression="i_id_person" />
        <asp:BoundField DataField="i_id_personlist" 
            HeaderText="i_id_personlist" 
            InsertVisible="False" ReadOnly="True" 
            SortExpression="i_id_personlist" />
        <asp:BoundField DataField="i_id_tool" HeaderText="i_id_tool" 
            SortExpression="i_id_tool" />
        <asp:BoundField DataField="i_count" HeaderText="i_count" 
            SortExpression="i_count" />
    </Columns>
</asp:GridView>
...
<asp:SqlDataSource ID="dsList" runat="server" 
    ConnectionString="<%$ ConnectionStrings:ConnectionString %>" 
    SelectCommand="selectByPersonList" SelectCommandType="StoredProcedure">
    <SelectParameters>
        <asp:Parameter Name="sel_min" Type="Int32" DefaultValue="10" />
    </SelectParameters>
</asp:SqlDataSource>