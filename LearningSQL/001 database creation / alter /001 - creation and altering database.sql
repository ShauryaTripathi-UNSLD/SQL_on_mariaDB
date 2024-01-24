--if a command doesn't runs on mariadb, it implies its meant to run on MYSQL


drop DATABASE db_0001;
CREATE DATABASE IF NOT EXISTS db_0001;
ALTER DATABASE db_0001 MODIFY NAME = db_0001_new;
-- to rename , follow this
--mysql -u your_username -p new_database_name < old_database_name.sql
    --$ mysqldump -u username -p"password" -R oldDbName > oldDbName.sql.
   -- $ mysqladmin -u username -p"password" create newDbName.
    --$ mysql -u username -p"password" newDbName < oldDbName.sql.

DROP DATABASE IF EXISTS db_0001;

--if multiple users are connected
--mysqladmin -u root -p flush-privileges
--or
--mysqladmin -u root -p reload
--or
alter DATABASE db_0001 set SINGLE_USER WITH ROLLBACK immediate;
