/*
Database creation Script for 2016 Capstone Project: Reaction Time Tester
By: Andy Tran
*/
use master
go

if exists 
(
	select	[name]
	from	sysdatabases
	where	[name] = 'atran26_Capstone2016'
)
		drop database atran26_Capstone2016
go

create database atran26_Capstone2016
go

use atran26_Capstone2016
go

-- Table Drops (Make sure these are in the proper order)
--01. UserTests
--02. Users
--03. Tests
if exists(select	[name] from	sysobjects where	[name] = 'dbo.UserTests')
	drop table dbo.UserTests
go
if exists(select	[name] from	sysobjects where	[name] = 'dbo.Tests')
	drop table dbo.Tests
go
if exists(select	[name] from	sysobjects where	[name] = 'dbo.Users')
	drop table dbo.Users
go

-- Table Creations (Make sure these are in the proper order)
--01. Users
--02. Tests
--03. UserTests
create table Users
(
	Username	nvarchar(20)	not null
		constraint PK_Username primary key clustered,
	Password	nvarchar(20) not null
)

create table Tests
(
	TestID		int		not null	identity(1,1)
		constraint PK_TestID primary key clustered,
	Test1Time	float	not null,
	Test2Time	float	not null,
	Test3Time	float	not null,
	TestAverage float	not null,
	TestDate	datetime
)

create table UserTests
(
	Username	nvarchar(20)	not null
		constraint FK_Username foreign key(Username) references Users(Username),
	TestID		int		not null			
		constraint FK_TestID foreign key(TestID) references Tests(TestID),

	constraint PK_Username_TestID primary key clustered (Username,TestID) 
)

