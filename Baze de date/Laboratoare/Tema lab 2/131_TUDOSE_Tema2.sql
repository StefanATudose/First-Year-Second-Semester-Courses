--Subiect I.
--1.
select *
from employees
where upper(last_name) LInullKE 'K%'; --raspuns : 6

--2.
select employee_id, last_name, first_name
from employees
where salary = (select min(salary) from employees);     --132 Olson TJ

--3.
select distinct e.employee_id, e.last_name
from employees e, employees ee
where ee.manager_id = e.employee_id and e.department_id = 30
order by e.last_name;

--4.
select e.employee_id, e.last_name, e.first_name, (select count(ee.employee_id) from employees ee where ee.manager_id = e.employee_id) "nr subordonati"
from employees e;

--5.
select distinct e.employee_id, e.last_name, e.first_name
from employees e
join employees ee
on e.last_name = ee.last_name and e.employee_id <> ee.employee_id;

--6.
select distinct d.department_id, d.department_name
from departments d
join employees e
on (select count(distinct e.job_id) from employees e where e.department_id = d.department_id) >= 2;

--SUBIECTUL II.
--7.
select distinct p.prod_id, p.prod_desc, (select sum(qty) from orders_tbl o where o.prod_id = p.prod_id)
from orders_tbl o
join products_tbl p
on o.prod_id = p.prod_id
where lower(prod_desc) like '%plastic%';

--8.
select cust_name, 'client'
from customer_tbl
union
select last_name || ' ' || first_name, 'employee'
from employee_tbl;

--9.
select distinct pp.prod_desc
from products_tbl p, orders_tbl o, employee_tbl e, orders_tbl oo, products_tbl pp
where o.sales_rep = e.emp_id and o.prod_id = p.prod_id and oo.sales_rep = e.emp_id and pp.prod_id = oo.prod_id and decode(instr(p.prod_desc, ' '), 0, 0, 1) = 1 and lower(substr(p.prod_desc, (instr(p.prod_desc, ' ')+1), 1)) = 'p';



--10
select c.cust_name
from customer_tbl c, orders_tbl o
where c.cust_id = o.cust_id and to_char(ord_date, 'DD') like '17';

--11
select e.last_name, e.first_name, ep.salary, ep.bonus
from employee_tbl e
join employee_pay_tbl ep
on e.emp_id = ep.emp_id
where (case when(ep.salary >= ep.bonus* 17) then ep.salary when(ep.salary < ep.bonus* 17) then ep.bonus * 17 end) < 32000;

--12
select distinct last_name, (select sum(o.qty) from orders_tbl o where o.sales_rep = e.emp_id)
from employee_tbl e
where (select sum(qty) from orders_tbl o where o.sales_rep = e.emp_id) > 50 or (select sum(qty) from orders_tbl o where o.sales_rep = e.emp_id) is null;

--13.
select distinct e.last_name, ep.salary, (select max(o.ord_date) from orders_tbl o where o.sales_rep = e.emp_id)        
from orders_tbl o, employee_tbl e, employee_pay_tbl ep
where sales_rep = e.emp_id and ep.emp_id = e.emp_id and (select count(ord_num) from orders_tbl o where sales_rep = e.emp_id) >= 2;

--14
select prod_id, prod_desc
from products_tbl p
where p.cost > (select sum(cost) from products_tbl)/(select count(cost) from products_tbl);

--15.
select last_name, first_name, salary, bonus, (select sum(all salary) from employee_pay_tbl), (select sum(all bonus) from employee_pay_tbl)
from employee_tbl e, employee_pay_tbl ep
where e.emp_id = ep.emp_id;

--16.
select distinct city 
from employee_tbl e, orders_tbl o
where o.sales_rep = e.emp_id and (select max(ord_num) from orders_tbl) = (select max(ord_num) from orders_tbl o where o.sales_rep = e.emp_id);

--17.
select distinct emp_id, last_name, decode(to_char(ord_date, 'MM'), '09', (select count(ord_num) "septembrie" from orders_tbl o where e.emp_id = o.sales_rep and (to_char(ord_date, 'MM') = '09')) , '10',(select count(ord_num)"octombrie" from orders_tbl o where e.emp_id = o.sales_rep and (to_char(ord_date, 'MM') = '10')), null) "septembrie sau octombrie"
from employee_tbl e, orders_tbl o
where e.emp_id = o.sales_rep and decode(to_char(ord_date, 'MM'), '09', 1, '10', 1, 0) = 1;

--18.
select cust_name, cust_city, cust_address
from customer_tbl 
where cust_id not in(
    select cust_id
    from customer_tbl
    natural join orders_tbl
) and cust_address like '0%' or cust_address like '1%' or cust_address like '2%' or cust_address like '3%' or cust_address like '4%' or cust_address like '5%' or cust_address like '6%' or cust_address like '7%' or cust_address like '8%' or cust_address like '9%';  --initial am folosit like '[0-9]%';, dar n a vrut

--19.
select e.emp_id, e.last_name, e.city, c.cust_id, c.cust_name, c.cust_city
from employee_tbl e, customer_tbl c, orders_tbl o
where e.emp_id = o.sales_rep and c.cust_id = o.cust_id and c.cust_city <> e.city;

--20.
select avg(all salary)
from employee_pay_tbl;

--21.
--a este corect, b nu compileaza pentru ca atributul salary face parte din employee_pay_tbl, nu din employee_tbl

--22.
select e.last_name, p.pay_rate
from employee_tbl e, employee_pay_tbl p
where (e.emp_id = p.emp_id) and p.pay_rate > (select max(p.pay_rate) from employee_tbl e, employee_pay_tbl p where e.emp_id = p.emp_id and upper(e.last_name) like '%LL%');

