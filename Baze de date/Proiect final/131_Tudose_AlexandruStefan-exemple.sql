--Cerinta proiect 12.
--1. Sa se afiseze numele agentilor care supravegheaza persoane fizice care au cel putin 2 ocupatii, precum si numele persoanelor fizice.
select distinct a.nume || ' ' || a.prenume "Agent", p.nume || ' ' || p.prenume "Subiect"
from agentt a, supraveghere s, persoana_fizica p, ocup_om oo
where a.agent_id = s.agent_id and s.subiect_id = p.subiect_id and p.subiect_id = oo.subiect_id
group by a.nume, a.prenume, p.nume, p.prenume
having count(oo.ocup_id) >= 2
order by a.nume || ' ' || a.prenume desc;
--am aici join pe 4 tabele, ordonare, grupari de date, functii grup, filtrare la nivel de grupuri


--2. Sa se afiseze codul subiectilor, coeficientul acestora de risc, si coeficientul de risc marit pentru cei suspectati ca au comis cel putin o
--crima cu mai mult de 3 luni in urma si care sunt supravegheati de cel putin 2 agenti. Marirea se va face astfel:
--Pentru cei cu un coeficient intre 1 si 3, el se va mari la 7; pentru cei cu un coeficient intre 4 si 6, el se va mari la 8;
--pentru cei cu un coeficient intre 7 si 8, el se va mari la 9; 
--pentru cei cu 9, va ramane neschimbat

select s.subiect_id, s.coef_risc, (case 
                                        when(s.coef_risc >=1 and s.coef_risc <= 3) then 7
                                        when(s.coef_risc >=4 and s.coef_risc <= 6) then 8
                                        when(s.coef_risc >=7 and s.coef_risc <= 9) then 9 end) "Coef_risc marit"
from subiect s
where s.subiect_id in(select supra.subiect_id from suspiciune_crima sc, supraveghere supra
       where s.subiect_id = sc.subiect_id and supra.subiect_id = s.subiect_id and add_months(sc.data_comitere, 3) <= sysdate
       group by supra.subiect_id having count(distinct supra.agent_id) >= 2);
--are cerere sincronizata cu 3 tabele, 2 functii de date (addmonths, sysdate), case, filtrare la nivel de linii(in subcerere)

--3. Sa se afiseze id-ul subiectului si cel al agentului in cazul operatiunilor de supraveghere ale tuturor agentilor care au salariul mai mare decat 20000, care au numele mai lung de 5 litere,
--iar a treia litera din prenume este r
with salut as (select agent_id from agentt where salariu > 20000)
select s.subiect_id, s.agent_id from supraveghere s, agentt a
where s.agent_id = a.agent_id and a.agent_id in (select agent_id from salut) and length (nume) > 5 and substr(lower(prenume), 3, 1) = 'r';
--are 3 functii pentru caractere(lower, substr, length), clauza with

--4. Sa se afiseze numele persoanelor fizice care au o ocupatie cu un venit mediu peste 2500 intr-o industrie cu un grad de risc peste 4
select p.nume from persoana_fizica p
where p.subiect_id in (select distinct oo.subiect_id from ocup_om oo, ocupatie o, industrie i
                            where oo.ocup_id = o.ocup_id and i.industrie_id = oo.industrie_id
                            and (venit_max+venit_min)/2 > 2500 and grad_risc > 4);
--are subcerere necorelata cu 3 tabele

--5. Ultimele cercetari arata ca veniturile maxime si minime pentru ocupatiile programator si tester s-au dublat.
--Sa se afiseze date despre toate ocupatiile, cu noile limite de venituri, ca atare
select ocup_id, nume_ocup, decode(lower(nume_ocup), 'programator', venit_min*2, 'tester', venit_min*2, venit_min) "venit minim actualizat",
    decode(lower(nume_ocup), 'programator', venit_max*2, 'tester', venit_max*2, venit_max) "venit maxim actualizat"
from ocupatie;
--are nvl si decode

--Cerinta 13
--1. Sa se actualizeze coeficientul de risc al subiectul cu codul 10034 cu valoarea coeficientului maxim dintre toti subiectii
update subiect
set coef_risc = (select max(coef_risc) from subiect)
where subiect_id = 10034;

--2. Sa se incrementeze cu 1 coeficientul de risc al subiectilor supravegheati de cel putin 2 agenti
update subiect s
set coef_risc = coef_risc+1
where (select count(distinct agent_id) from supraveghere supra where s.subiect_id = supra.subiect_id ) >= 2;

--3. Sa se dubleze bugetul de combatere a crimelor alocat pentru cele care sunt comise minim 3 subiecti
update crime c
set buget_alocat = buget_alocat * 2
where (select count(distinct sus.subiect_id) from suspiciune_crima sus where c.crima_id = sus.crima_id) >= 3;

--4. Sa se stearga instanta de supraveghere care a inceput in urma cu cel mai mult timp
delete from supraveghere
where data_incepere = (select min(data_incepere) from supraveghere);

--5. Sa se stearga subiectii care nu sunt urmariti de niciun agent si nu sunt suspecti de nicio crima
delete from subiect s
where (select count (distinct agent_id) from supraveghere supra where s.subiect_id = supra.subiect_id) = 0
 and (select count (distinct crima_id) from suspiciune_crima sus where s.subiect_id = sus.subiect_id) = 0;
 
--6. Sa se stearga sediile la care nu este atribuit niciun agent
delete from sediu s
where (select count(agent_id) from agentt a where a.sediu_id = s.sediu_id) =0;

commit;


--Cerinta 16
--Cerinta operatia outer join: 
-- Sa se efectueze un studiu pe piata muncii utilizand datele adunate: sa se aficeze numele tuturor persoanele fizice 
--care nu au ocupatie si toate ocupatiile inregistrate in baza de date in care nu presteaza niciun muncitor
select pf.nume || ' ' || pf.prenume, o.nume_ocup from subiect s
FULL JOIN ocup_om oo on s.subiect_id = oo.subiect_id
FULL JOIN ocupatie o on oo.ocup_id = o.ocup_id
FULL JOIN persoana_fizica pf on s.subiect_id = pf.subiect_id
where (pf.subiect_id is not null and oo.ocup_id is null) or (oo.subiect_id is null and o.ocup_id is not null);

--Cerinta 1 division
--Sa se afiseze numele agentilor care supravegheaza toti subiectii cu un coeficient de risc egal cu 4
select distinct nume || ' ' || prenume "Nume"
from agentt a join supraveghere s
on a.agent_id = s.agent_id
where not exists(
        select 0 from subiect s
        where s.coef_risc = 4
        and not exists(
            select 0 from supraveghere s1
            where s.subiect_id = s1.subiect_id
            and s.agent_id = s1.agent_id));
            
--Cerinta 2 division
--Sa se afiseze numele persoanelor fizice interesate de toate activitatile cu un risc de criminalitate sub 3 inclusiv
select distinct nume || ' ' || prenume "Nume persoana fizica"
from persoana_fizica pf
join subiect s on s.subiect_id = pf.subiect_id
join interes_om i on i.subiect_id = s.subiect_id
where not exists(
        select 0 from interese ii
        where risc_criminalitate <= 3
        and not exists(
            select 0 from interes_om i1
            where ii.interes_id = i1.interes_id
            and i.subiect_id = i1.subiect_id));

