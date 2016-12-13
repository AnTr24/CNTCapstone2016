/*
Procedure creation Script for 2016 Capstone Project: Reaction Time Tester
By: Andy Tran
*/
use atran26_Capstone2016
go

/* Template for Copy&Paste
if exists(select[name] from sys.objects where [name]='ProcedureName')
	drop procedure ProcedureName
go
create procedure ProcedureName
@variables
as
return 0
go
*/

/***************************************************
Procedures in this block are used for the 
Reaction Time Tester Application/UI:

List of procedures:
-ValidateUser
-AddUser
-AddTestResults

Program Procedures START
****************************************************/

/*
Procedure Name:		ValidateUser
Arguments:	@username nvarchar(20)	:	Supplied Username
			@password nvarchar(20)	:	Supplied Password	
ERROR Codes:		0 - success
					1 - Invalid username/password
Description:	Procedure for login validation
*/
if exists(select[name] from sys.objects where [name]='ValidateUser')
	drop procedure ValidateUser
go
create procedure ValidateUser
@username nvarchar(20),
@password nvarchar(20)
as
if not exists(	select Username from atran26_Capstone2016.dbo.Users		--Check user and password combination
				where Username = @username and Password = @password)
	return 1
					
return 0										
go

/*
Procedure Name:		AddUser
Arguments:	@username nvarchar(20)	:	Supplied Username
			@password nvarchar(20)	:	Supplied Password	
ERROR Codes:		0 - success
					1 - User already exists
					2 - Query error
Description:	Procedure for adding user to database
*/
if exists(select[name] from sys.objects where [name]='AddUser')
	drop procedure AddUser
go
create procedure AddUser
@username nvarchar(20),
@password nvarchar(20)
as
if exists(	select Username from atran26_Capstone2016.dbo.Users		
			where Username = @username)
	return 1

begin transaction
insert into atran26_Capstone2016.dbo.Users(Username,Password)
values (@username,@password)
if @@ERROR <> 0
	begin
	rollback transaction
	return 2
	end

commit transaction					
return 0										
go

/*
Procedure Name:		AddTestResults
Arguments:	@username nvarchar(20)	:	Supplied Username
			@Test1Time float		:	Test 1 Result
			@Test2Time float		:	Test 2 Result
			@Test3Time float		:	Test 3 Result
			@TestAverage float		:	Overall Average
ERROR Codes:		0 - success
					1 - Invalid username
					2 - Error on Tests table insert
					3 - Error on UserTests insert
Description:	Adds test results and its association to a user
*/
if exists(select[name] from sys.objects where [name]='AddTestResults')
	drop procedure AddTestResults
go
create procedure AddTestResults
@username nvarchar(20),
@Test1Time float,
@Test2Time float,
@Test3Time float,
@TestAverage float
as

--Check if user exists before inserting
if not exists(	select Username from atran26_Capstone2016.dbo.Users		
				where Username = @username)
	return 1


begin transaction
--Attempt insert of test data
insert into atran26_Capstone2016.dbo.Tests
(Test1Time,Test2Time,Test3Time,TestAverage,TestDate)
values
(@Test1Time,@Test2Time,@Test3Time,@TestAverage,getdate())
if @@ERROR <> 0
	begin
	rollback transaction
	return 2
	end

--Attempt association of the test instance to the user
insert into atran26_Capstone2016.dbo.UserTests
(Username,TestID)
values
(@username, cast(IDENT_CURRENT('atran26_Capstone2016.dbo.Tests') as int))
if @@ERROR <> 0
	begin
	rollback transaction
	return 3
	end

commit transaction					
return 0										
go

/******************************************************
Program Procedures END
******************************************************/
/***************************************************
Procedures in this block are used for the 
Reaction Time Tester Webpage:

List of procedures:
-GetAllResults
-GetUserTestHistory

Webpage Procedures START
******************************************************/
/*
Procedure Name:		GetAllResults
Arguments:			[OPTIONAL]@searchFIlter
ERROR Codes:		0 - success
					1 - error on query
Description:	Gets all the tests results stored For
				each user. Results can be filtered, will grab all results
				with usernames beginning with the filter 
*/
if exists(select[name] from sys.objects where [name]='GetAllResults')
	drop procedure GetAllResults
go
create procedure GetAllResults
@searchFilter nvarchar(20) = ''
as

if @searchFilter is null
	set @searchFilter = ''

select	UT.Username as 'Username',
		T.Test1Time as 'Test1',
		T.Test2Time as 'Test2',
		T.Test3Time as 'Test3',
		T.TestAverage as 'Average',
		T.TestDate as 'Date Taken'
from atran26_Capstone2016.dbo.UserTests as UT 
inner join atran26_Capstone2016.dbo.Tests as T
on UT.TestID = T.TestID
where UT.Username like @searchFIlter + '%'
order by T.TestDate desc
if @@ERROR <> 0
	return 1
return 0
go

/*
Procedure Name:		GetUserTestHistory
Arguments:			@username
ERROR Codes:		0 - success
					1 - user doesn't exist
Description:	Gets all the test results for a user
*/
if exists(select[name] from sys.objects where [name]='GetUserTestHistory')
	drop procedure GetUserTestHistory
go
create procedure GetUserTestHistory
@username nvarchar(20)
as
if not exists(	select Username from atran26_Capstone2016.dbo.Users 
				where Username = @username)
	return 1

select	T.Test1Time as 'Test1',
		T.Test2Time as 'Test2',
		T.Test3Time as 'Test3',
		T.TestAverage as 'Average',
		T.TestDate as 'Date Taken'
from atran26_Capstone2016.dbo.UserTests as UT 
inner join atran26_Capstone2016.dbo.Tests as T
on UT.TestID = T.TestID
where UT.Username = @username
order by T.TestDate desc
return 0
go

/*
Procedure Name:		GetUserAvgTime
Arguments:			@username
ERROR Codes:		0 - success
					1 - user doesn't exist
Description:	Gets the average of the user based on all historical data
*/
if exists(select[name] from sys.objects where [name]='GetUserAvgTime')
	drop procedure GetUserAvgTime
go
create procedure GetUserAvgTime
@username nvarchar(20)
as
if not exists(	select Username from atran26_Capstone2016.dbo.Users 
				where Username = @username)
	return 1

select AVG(T.TestAverage) as 'Average'
from atran26_Capstone2016.dbo.UserTests as UT
inner join atran26_Capstone2016.dbo.Tests as T
on UT.TestID = T.TestID
where UT.Username = @username

return 0
go

/*
Procedure Name:		GetUserFastestTime
Arguments:			@username
ERROR Codes:		0 - success
					1 - user doesn't exist
Description:	Gets the fastest time of the user based on all historical data
*/
if exists(select[name] from sys.objects where [name]='GetUserFastestTime')
	drop procedure GetUserFastestTime
go
create procedure GetUserFastestTime
@username nvarchar(20)
as
if not exists(	select Username from atran26_Capstone2016.dbo.Users 
				where Username = @username)
	return 1

select top 1 
		T.Test1Time as 'Test1',
		T.Test2Time as 'Test2',
		T.Test3Time as 'Test3',
		T.TestAverage as 'Average',
		T.TestDate as 'Date Taken'
from atran26_Capstone2016.dbo.UserTests as UT
inner join atran26_Capstone2016.dbo.Tests as T
on UT.TestID = T.TestID
where UT.Username = @username
order by T.TestAverage asc
return 0
go

/*
Procedure Name:		GetUserTestCount
Arguments:			@username
ERROR Codes:		0 - success
					1 - user doesn't exist
Description:	Gets the fastest time of the user based on all historical data
*/
if exists(select[name] from sys.objects where [name]='GetUserTestCount')
	drop procedure GetUserTestCount
go
create procedure GetUserTestCount
@username nvarchar(20)
as
if not exists(	select Username from atran26_Capstone2016.dbo.Users 
				where Username = @username)
	return 1
select count(TestID) as 'Test Count'
from atran26_Capstone2016.dbo.UserTests
where Username = @username
return 0
go
/******************************************************
Webpage Procedures END
******************************************************/