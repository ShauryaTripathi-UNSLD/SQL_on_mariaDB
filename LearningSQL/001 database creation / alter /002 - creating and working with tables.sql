-- learnt primary KEY
-- there are two ways to create a table, first graphically and another using QUERY
CREATE DATABASE IF NOT EXISTS db_0001;
USE db_0001;
CREATE Table tblGender(
    ID int NOT NULL PRIMARY KEY,
    Gender nvarchar(50) NOT NULL
);
--The nvarchar data type is used to store variable-length Unicode character data.
-- It can hold both alphanumeric characters and special characters from different languages and character sets. 
--The "n" in nvarchar stands for "national," indicating that it supports Unicode characters.