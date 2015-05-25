CREATE PROCEDURE dbo.selectAvgPersonList
	@sum int = 0 output
AS
	SELECT @sum = SUM(i_count) from tbPersonList
RETURN @sum