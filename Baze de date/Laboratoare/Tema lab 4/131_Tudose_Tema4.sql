--1
select s_last
from student s
where not exists(
    select 1 
    from enrollment e
    where s.s_id = e.s_id
    and exists
        (select 'x' 
        from enrollment ee
        where ee.s_id = e.s_id
        and ee.grade is null));


--2.
select f_last 
from faculty f join course_section c
on f.f_id = c.f_id 
where max_enrl = (select max(max_enrl) from course_section) 
    or c.loc_id = (select loc_id from location where capacity =
        (select max(capacity) from location));
        
--3.
select avg((
    select distinct l.capacity
    from location l
    join course_section c on l.loc_id = c.loc_id
    join faculty f on c.f_id = f.f_id
    where f.f_first || ' ' || f.f_last = 'Teresa Marx'
    union
    select c.max_enrl 
    from course_section c 
    join enrollment e on c.c_sec_id = e.c_sec_id
    join student s on e.s_id = s.s_id
    where s.s_last || ' ' || s.s_first = 'Jones Tammy'
)) "medie" from dual;

--4.
select course_no, course_name from course 
where (select count(*) from course where course_name like '%Java%')=0 or course_name like '%Java%';


--5.
select distinct l.loc_id 
from location l
join course_section c on l.loc_id = c.loc_id
join course c0 on c0.course_no = c.course_no
where lower(course_name) like '%database%' or lower(course_name) like '%c++%';

