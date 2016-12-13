--Testing Procedures

use atran26_Capstone2016
go


select * from atran26_Capstone2016.dbo.Users
select * from atran26_Capstone2016.dbo.UserTests
select * from atran26_Capstone2016.dbo.Tests
go

--testing ValidateUser
declare @returnCode int = 0
execute @returnCode = atran26_Capstone2016.dbo.ValidateUser 'Bob','Pw123'

select @returnCode as 'Return Code'
go

--testing AddUser
declare @returnCode int = 0
execute @returnCode = atran26_Capstone2016.dbo.AddUser 'Test','Pw123'

select @returnCode as 'Return Code'
go

--testing AddTestResults
declare @returnCode int = 0
declare @date datetime = GETDATE()
execute @returnCode = atran26_Capstone2016.dbo.AddTestResults 'Test', 6.80,5.50,0.02,4.08
select @returnCode as 'Return Code'
go

--testing GetAllResults
declare @returnCode int = 0
declare @searchFilter nvarchar(20) = ''
execute @returnCode = atran26_Capstone2016.dbo.GetAllResults @searchFilter
select @returnCode as 'Return Code'
go

--testing GetUserTestHistory
declare @returnCode int = 0
declare @searchFilter nvarchar(20) = 'Test'	--for some reason nvarchar limit must be specified 
											--[SOLVED] Given nvarchar(n) = 'Test', if 'n' is not specified,
											--defaults to nvarchar(1) so 'Test' is truncated to 'T'
execute @returnCode = atran26_Capstone2016.dbo.GetUserTestHistory @searchFilter
select @returnCode as 'Return Code'
go

--testing GetUserAvgTime
declare @returnCode int = 0
declare @searchFilter nvarchar(20) = 'jack'
execute @returnCode = atran26_Capstone2016.dbo.GetUserAvgTime @searchFilter
select @returnCode as 'Return Code'
select * 
from atran26_Capstone2016.dbo.Tests as T
inner join atran26_Capstone2016.dbo.UserTests as UT
on T.TestID = UT.TestID
where UT.Username = @searchFilter
go

--testing GetUserFastestTime
declare @returnCode int = 0
declare @searchFilter nvarchar(20) = 'jack'
execute @returnCode = atran26_Capstone2016.dbo.GetUserFastestTime @searchFilter
select @returnCode as 'Return Code'
select UT.Username,T.TestID,T.Test1Time,T.Test2Time,T.Test3Time,T.TestAverage
from atran26_Capstone2016.dbo.Tests as T
inner join atran26_Capstone2016.dbo.UserTests as UT
on T.TestID = UT.TestID
where UT.Username = @searchFilter
go

--testing GetUserTestCount
declare @returnCode int = 0
declare @searchFilter nvarchar(20) = 'jack'
execute @returnCode = atran26_Capstone2016.dbo.GetUserTestCount @searchFilter
select @returnCode as 'Return Code'
select UT.Username,T.TestID,T.Test1Time,T.Test2Time,T.Test3Time,T.TestAverage
from atran26_Capstone2016.dbo.Tests as T
inner join atran26_Capstone2016.dbo.UserTests as UT
on T.TestID = UT.TestID
where UT.Username = @searchFilter
go