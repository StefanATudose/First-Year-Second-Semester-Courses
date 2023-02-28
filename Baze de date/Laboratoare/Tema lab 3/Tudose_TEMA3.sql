--Tema lab 3 TUDOSE Alexandru-Stefan 131
--1.
select s_id "Cod", s_last "Student sau curs", 'student' "tip"
from student s
join faculty f
on s.f_id = f.f_id 
where lower(f.f_last) = 'brown'
union
select distinct c.course_no "Cod", c.course_name "Student sau curs", 'curs' "tip"
from course c join course_section cs on c.course_no = cs.course_no
join faculty f on f.f_id = cs.f_id 
where lower(f_last) = 'brown';

--2. aici nuj ce sa-i fac ca e fix problema cu not in care a aparut si in laboratorul 8(cea pe care v-am scris-o in mesaj pe teams)
select s.s_id, s.s_last
from student s, enrollment e, course_section css
where s.s_id = e.s_id and e.c_sec_id = css.c_sec_id  
and 'Database Management' in (select distinct c.course_name from course c where css.course_no = c.course_no);
and 'Programming in C++' not in (select distinct c.course_name from course c where css.course_no = c.course_no and c.course_name is not null);
--c.course_name = 'Database Management' and c.course_name <> 'Programming in C++';

--3.
select distinct s.s_id, s.s_last
from student s, enrollment e
where s.s_id = e.s_id and (grade = 'C' or grade is null);

--4.
select loc_id, bldg_code, capacity
from location 
where capacity = (select max(capacity) from location);

--5.
drop table t;
CREATE TABLE t (id NUMBER PRIMARY KEY);
INSERT INTO t VALUES(1);
INSERT INTO t VALUES(2);
INSERT INTO t VALUES(4);
INSERT INTO t VALUES(5);
INSERT INTO t VALUES(8);
INSERT INTO t VALUES(9);

select min(id)+1                                                        --asta nu merge din pacate pentru 1 si 9, nuj cum sa fac altfel
from t t1
where not exists (select 1 from t t2 where t2.id = t1.id+1)
union
select max(id)-1
from t t1
where not exists (select 1 from t t2 where t2.id = t1.id -1);

--6.
select f.f_id "Cod profesor", 'Da (' || (select count(s_id) from student s where s.f_id = f.f_id) || ')' "Student",
'Da (' || (select count(c_sec_id) from course_section css where css.f_id = f.f_id) || ')'  "Curs"
from faculty f
where (select count(s_id) from student s where s.f_id = f.f_id) <> 0 and (select count(c_sec_id) from course_section css where css.f_id = f.f_id) <> 0
union
select f.f_id "Cod profesor", 'Da (' || (select count(s_id) from student s where s.f_id = f.f_id) || ')' "Student",
'Nu' "Curs"
from faculty f
where (select count(s_id) from student s where s.f_id = f.f_id) <> 0 and (select count(c_sec_id) from course_section css where css.f_id = f.f_id) = 0
union
select f.f_id "Cod profesor", 'Nu' "Student", 'Da (' || (select count(c_sec_id) from course_section css where css.f_id = f.f_id) || ')'  "Curs"
from faculty f
where (select count(s_id) from student s where s.f_id = f.f_id) = 0 and (select count(c_sec_id) from course_section css where css.f_id = f.f_id) <> 0
union
select f.f_id "Cod profesor", 'Nu' "Student", 'Nu'  "Curs"
from faculty f
where (select count(s_id) from student s where s.f_id = f.f_id) = 0 and (select count(c_sec_id) from course_section css where css.f_id = f.f_id) = 0;


--7.
select t1.term_desc, t2.term_desc
from term t1 join term t2 on substr(t1.term_desc, 1, length(t1.term_desc)-1) = substr(t2.term_desc, 1, length(t2.term_desc)-1)
and t1.term_desc != t2.term_desc;

--8
select distinct s.s_id, s.s_last
from student s join enrollment e on s.s_id = e.s_id 
join course_section css on e.c_sec_id = css.c_sec_id
join course c on css.course_no = c.course_no
join course cc on substr(cc.course_name, 5, 1) = substr(c.course_name, 5, 1);

--9
select distinct c1.course_no, c2.course_no
from course c1, course c2, course_section css1, course_section css2, term t1, term t2
where c1.course_no > c2.course_no and c1.course_no = css1.course_no
and css1.term_id = t1.term_id and c2.course_no = css2.course_no
and css2.term_id = t2.term_id and t1.term_id = t2.term_id;

--10
select distinct c.course_no, c.course_name, t.term_desc, max_enrl
from course c, course_section css, term t
where c.course_no = css.course_no and css.term_id = t.term_id and css.max_enrl < all (select max_enrl from course_section css1 where css1.loc_id = 1);

--11
select distinct c.course_name, css.max_enrl 
from course c join course_section css on css.course_no = c.course_no
where css.max_enrl = (select min(max_enrl) from course_section); 

--12
select f.f_last, round(avg(nvl(css.max_enrl, 0)))
from faculty f join course_section css on css.f_id = f.f_id
group by f.f_last;

--13
select f.f_last, count(s.s_id)
from faculty f join student s on s.f_id = f.f_id
group by f.f_last
having count(s.s_id) >= 3;

--14.
select distinct c.course_name, (select max(l.capacity) from location l, course_section css
where c.course_no = css.course_no and css.loc_id = l.loc_id), ll.loc_id
from course c, location ll, course_section csss
where c.course_no = csss.course_no and csss.loc_id = ll.loc_id and ll.capacity = (select max(l.capacity) from location l, course_section css
where c.course_no = css.course_no and css.loc_id = l.loc_id);

--15.
select avg(max_enrl) from term t, course_section css
where t.term_id = css.term_id and lower(t.term_desc) LIKE '%2007%';