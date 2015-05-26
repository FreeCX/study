create user u1 identified by /
default tablespace system
quota 1m on system;
create user u2 identified by / 
default tablespace system
quota 1m on system;
create sequence Seq1
maxvalue 3 minvalue 1 start with 2;
select Seq1.nextval from dual;
select Seq1.nextval from dual;
select Seq1.nextval from dual;
drop sequence Seq1;
create table RefCodes(At1 NUMBER, At2 VARCHAR2(5));
insert into RefCodes values (1, 'text1');
insert into RefCodes values (2, 'text2');
select * from RefCodes;
grant select on RefCodes to u1;
connect u1/ as sysdba
select * from RefCodes;
connect / as sysdba
create view vu2 as select * from RefCodes where At1 > 1 with check option;
grant insert, select on vu2 to u2;
connect u2/ as sysdba
insert into vu2 values (3, 'text3');
select * from vu2;
drop user u1;
drop user u2;
drop view vu2;
drop table RefCodes;