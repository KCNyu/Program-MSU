use firstdb;
create table Test (
    personid INT(50) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    firstname VARCHAR(35),
    middlename VARCHAR(50),
    lastname VARCHAR(50) default 'pushkin'
);
