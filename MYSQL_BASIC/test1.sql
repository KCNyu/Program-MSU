use firstdb;
insert into kadry values('ivan', 'i.', 'ivanov');
select * from kadry;
insert into kadry values('valentina', 'v.', 'ivanova');
select * from kadry;
INSERT INTO kadry VALUES('ivan','p.','petrov');
SELECT * FROM kadry;
SELECT * FROM kadry WHERE firstname = 'ivan';
SELECT * FROM kadry WHERE lastname like 'iva%';
