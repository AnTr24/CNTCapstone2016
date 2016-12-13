use atran26_Capstone2016
go

insert into Users(Username,Password)
values ('Bob','Pw123')
go

insert into Tests(Test1Time,Test2Time,Test3Time,TestAverage,TestDate)
values (1.00,0.25,0.500,0.60,GETDATE())
go

insert into UserTests
values ('Bob',1)
go

select * from dbo.Users
go
select * from dbo.Tests
go
select * from dbo.UserTests
go