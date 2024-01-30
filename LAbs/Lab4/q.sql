-- Active: 1705570679784@@127.0.0.1@3306@LAB4
--run via mariadb, not sql, same but little different
DROP DATABASE LAB4;
CREATE DATABASE IF NOT EXISTS LAB4;
use LAB4;
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
INSERT INTO Orders (O_NUM, AMT, ORDER_DATE, C_NUM, S_NUM)
VALUES
(3001, 1860, '2024-01-03', 2008, 1007),
(3003, 7670, '2022-07-03', 2001, 1001),
(3002, 0, '2024-01-03', 2007, 1004),
(3005, 5160, '2023-10-03', 2003, 1007),
(3006, 1095, '2023-10-03', 2008, 1007),
(3009, NULL, '2024-01-04', 2002, 1007),
(3007, 5570, '2024-01-04', 2004, 1007),
(3008, 4723, '2023-10-05', 2006, 1007),
(3010, NULL, '2022-07-06', 2004, 1007),
(3011, 1095, '2022-07-03', 2006, 1007);
select*from Orders;
insert into Customers Values
(2001, 'Hoffman', 'London', 100, 1001),
(2002, 'Tiffiany', 'Rome', 200, 1003),
(2003, 'Liu', 'SanJose', 200, 1002),
(2004, 'Thomas', 'Berlin', 300, 1002),
(2006, 'Clara', 'London', 100, 1001),
(2008, 'Ariana', 'SanJose', 300, 1007),
(2007, 'Duke', 'Rome', 100, 1004);
select * from Customers;
insert into Sales_People values
(1001, 'Jessica', 'London' ,0.12),
(1002, 'Robert', 'SanJose' ,0.13),
(1003, 'Alex', 'London' ,0.11),
(1004, 'Mathew', 'Barcelona' ,0.15),
(1007, 'Rihana', 'New York' ,0.10);
Select * from Sales_People;

--Q1
SELECT * FROM Orders WHERE AMT IS NOT NULL;
--Q2
SELECT Sales_People.*, Customers.`Rating`
FROM `Sales_People`   
JOIN `Customers` ON Sales_People.S_NUM = Customers.S_NUM
ORDER BY Sales_People.City, Customers.Rating DESC;
select * from Customers order by `Rating` DESC;
--Q3
SELECT * FROM Customers where Rating > 100 or `City` = 'Rome';
--Q4
SELECT *
FROM Customers
WHERE S_NUM IN (
    SELECT S_NUM
    FROM Sales_People
    WHERE S_NAME = 'Jessica' OR S_NAME = 'Robert'
);
--Q5
SELECT * FROM `Customers` where `C_NAME` LIKE 'T%' or `C_NAME` LIKE 'H%';
--Q6
SELECT COUNT(*) FROM `Orders` WHERE MONTH(`ORDER_DATE`) = 10 AND DAY(`ORDER_DATE`) = 3;

--Q7
SELECT C_NUM, MIN(AMT) as Minimum_Amt
from `Orders`
where AMT>0
GROUP By `C_NUM`
ORDER BY AMT;  
--Q8
SELECT ORDER_DATE, COUNT(DISTINCT S_NUM) AS SalespeopleCount
FROM Orders
GROUP BY ORDER_DATE;
--Q9

SELECT City, MAX(Rating) as highest_rating
from `Customers`
GROUP By `City`
ORDER BY `Rating`;  

--Q10
select Rating,C_NAME,C_NUM
from `Customers`
ORDER BY Rating desc;

select COUNT(*) from `Customers`;



