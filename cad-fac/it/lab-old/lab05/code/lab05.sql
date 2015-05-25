CREATE PROCEDURE dbo.selectByPersonList
	@sel_min int
AS
	SELECT i_id_person, i_id_personlist, i_id_tool, i_count 
        from tbPersonList where i_count < @sel_min

CREATE PROCEDURE dbo.selectByMinMax
	@sel_min int,
	@sel_max int
AS
	SELECT i_id_list, i_id_tool, i_id_department, i_count 
        from tbLists where i_count between @sel_min and @sel_max

CREATE PROCEDURE dbo.selectByCountry
	@sel_country varchar(50)
AS
	SELECT i_id_manuf, vc_name, vc_country 
        from tbManufactured where vc_country = @sel_country