use atran26_Capstone2016
go

drop table atran26_Capstone2016.dbo.TestTable
go
create table TestTable
(
	teststring	nvarchar(100)	not null
)
go

create procedure TestProcedure
@teststring nvarchar(100)
as
insert into atran26_Capstone2016.dbo.TestTable
values (@teststring )
go

select * from atran26_Capstone2016.dbo.TestTable