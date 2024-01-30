-- Active: 1705570679784@@127.0.0.1@3306@LAB3
show databases;
create DATABASE if not exists LAB3;
use LAB3;
create table Sales_People(
S_NUM int(4),
S_NAME varchar(10),
City varchar(10),
Comm Decimal(3,2));
create table Customers(
C_NUM int(4),
C_NAME varchar(10),
City varchar(10),
Rating int(4),
S_NUM int (4));
create table Orders(
O_NUM int (4),
AMT Decimal (7,2),
ORDER_DATE date,
C_NUM int (4),
S_NUM int (4));

truncate table Orders;
INSERT INTO Orders
VALUES 
(3001,1860,'2024-01-03',2008, 1007),
(3003, 7670, '2022-07-03', 2001, 1001),
(3002, 1900,'2024-01-03', 2007 ,1004),
(3005 ,5160 ,'2023-10-03', 2003 ,1007),
(3006 ,1095 ,'2023-10-03' ,2008, 1007),
(3009, 1713 ,'2024-01-04' ,2002 ,1007),
(3007 ,5570 ,'2024-01-04' ,2004 ,1007),
(3008 ,4723 ,'2023-10-05' ,2006 ,1007),
(3010 ,1309 ,'2022-01-06', 2004 ,1007),
(3011 ,9891 ,'2022-07-03' ,2006 ,1007);
select*from orders;
insert into Customers Values
(2001, 'Hoffman', 'London' ,100 ,1001),
(2002, 'Tiffiany', 'Rome' ,200 ,1003),
(2003, 'Liu', 'SanJose' ,200 ,1002),
(2004, 'Thomas', 'Berlin' ,300 ,1002),
(2006, 'Clara', 'London' ,100 ,1001),
(2008, 'Ariana', 'SanJose' ,300 ,1007),
(2007, 'Duke', 'Rome' ,100 ,1004);
select * from Customers;
insert into Sales_People values
(1001, 'Jessica', 'London' ,0.12),
(1002, 'Robert', 'SanJose' ,0.13),
(1003, 'Alex', 'London' ,0.11),
(1004, 'Mathew', 'Barcelona' ,0.15),
(1007, 'Rihana', 'New York' ,0.10);
Select * from Sales_People;
select * from Customers where (Rating > 100 or CITY = 'Rome');
select S_NAME, CITY from Sales_People where City = 'London' and COMM > 0.10;
select * from orders where AMT > 1000;
select * from customers where S_NUM = 1001 ;
select O_NUM, AMT, ORDER_DATE from Orders;