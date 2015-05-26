drop table emp;
drop table dept;
create table dept (
    deptno number(3),
    dname varchar2(15),
    loc varchar2(15),
    constraint dname_ukey unique (dname, loc)
);
create table emp (
    empno number(5) primary key,
    ename varchar2(25),
    job varchar2(20),
    mgr number(5) constraint mgr_fkey
    references emp,
    hiredate date,
    sal number(7,2),
    comm number(5,2),
    deptno number(3) not null
);
alter table dept
    add primary key (deptno);
alter table emp
add constraint dept_fkey foreign key (deptno) references dept
    modify (ename varchar2(15) not null);
insert into dept values (1, 'edited-dept', 'dallas');
insert into dept values (2, 'unique-dept', 'ny');
insert into emp values (1, 'mr.black', 'rocket engines', null, null, 3.3, 4, 1);
insert into emp values (2, 'mr.white', 'test inc.', null, null, 2.71, 3, 2);
insert into emp values (3, 'mr.green', 'ink', null, null, 3.3, 2, 1);
select * from dept;
select * from emp;
lock table emp in share mode;
update emp set sal = sal * 1.1 where deptno in 
    (select deptno from dept where loc = 'dallas');
commit;
select * from dept; 
select * from emp;