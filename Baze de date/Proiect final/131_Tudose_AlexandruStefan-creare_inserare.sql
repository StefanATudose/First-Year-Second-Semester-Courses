drop sequence secv_id;
drop table OCUP_OM;
drop table SUPRAVEGHERE;
drop table SUSPICIUNE_CRIMA;
drop table PERSOANA_JURIDICA;
drop table PERSOANA_FIZICA;
drop table OCUPATIE;
drop table INTERES_OM;
drop table SUBIECT;
drop table INTERESE;
drop table INDUSTRIE;
drop table CRIME;
drop table AGENTT;
drop table SEDIU;
drop table PUNCT_SUPRAVEGHERE;


create sequence secv_id
increment by 1
start with 10000
maxvalue 99999
cycle
nocache;

create table PUNCT_SUPRAVEGHERE(
    pct_supra_id number(5) constraint pk_pct_suprav primary key,
    tip varchar(20) constraint nn_tip_pctsupra not null,
    data_amplasare date default sysdate,
    proximitate_subiect number(4),
    nivel_compromitere number(1)
);

create table SEDIU(
    sediu_id number(5) constraint pk_sed primary key,
    nume varchar(20) constraint nn_nume_sediu not null,
    oras varchar(15),
    strada varchar(15),
    nr_strada number(4)
);

create table AGENTT(
    agent_id number(5) constraint pk_age primary key,
    nume varchar(10) constraint nn_nume_age not null,
    prenume varchar(10) constraint nn_prenume_age not null,
    salariu number(6),
    hire_date date,
    sediu_id number(5) constraint fk_sed_age references SEDIU(sediu_id),
    rang number(1)
);

create table CRIME(
    crima_id number(5) constraint pk_crime primary key,
    nume varchar(15) constraint nn_nume_crime not null,
    nivel_sfidare_stat number(1),
    buget_alocat number(9)
);

create table INDUSTRIE(
    industrie_id number(5) constraint pk_ind primary key,
    nume varchar(15) constraint nn_nume_ind not null,
    contribuit_pib varchar(12),
    grad_risc number(1)
);

create table INTERESE(
    interes_id number(5) constraint pk_int primary key,
    nume varchar(25) constraint nn_nume_int not null,
    risc_criminalitate number(1),
    cost_mediu number(6)
);

create table SUBIECT(
    subiect_id number(5) constraint pk_subiect primary key,
    pct_supra_id number(5) constraint fk_pct_suprav_sub references PUNCT_SUPRAVEGHERE(pct_supra_id) constraint un_pct_supra_sub unique,
    coef_risc number(2)
);

create table INTERES_OM(
    interes_id number(5),
    subiect_id number(5) constraint fk_sub_int_om references SUBIECT(subiect_id) on delete cascade,
    constraint pk_int_om primary key(interes_id, subiect_id),
    constraint fk_int_int_om foreign key(interes_id) references INTERESE(interes_id)
);



create table OCUPATIE(
    ocup_id number (5) constraint pk_ocup primary key,
    nume_ocup varchar(15) constraint nn_nume_ocup not null,
    venit_max number(6) constraint nn_vmax_ocup not null,
    venit_min number(6) constraint nn_vmin_ocup not null
);

create table PERSOANA_FIZICA(
    subiect_id number(5) constraint pk_pers_fiz primary key,
    cnp varchar(14) constraint nn_cnp_persfiz not null constraint un_cnp_persfiz unique,
    nume varchar (15) constraint nn_nume_persfiz not null,
    prenume varchar (15) constraint nn_prenume_persfiz not null,
    data_nastere date,
    serie_ci varchar(3),
    nr_ci varchar(7)
);

create table PERSOANA_JURIDICA(
    subiect_id number(5) constraint pk_pers_jur primary key,
    nr_inreg varchar(15) constraint nn_inreg_pers_jur not null constraint un_inreg_persjur unique,
    nr_fiscal varchar(15)constraint nn_fisc_pers_jur not null constraint un_fisc_persjur unique,
    cod_caen varchar(5) constraint nn_caen_persjur not null,
    data_infiintare date,
    cifra_afaceri varchar(10),
    actionar_principal varchar(25),
    nume varchar(20) constraint nn_nume_persjur not null
);

create table SUSPICIUNE_CRIMA(
    subiect_id number(5) constraint fk_sub_sus references SUBIECT(subiect_id),
    crima_id number(5) constraint fk_crima_sus references CRIME(crima_id),
    data_comitere date constraint nn_data_sus not null,
    durata_comitere number(3) default 1,
    constraint pk_sus primary key(subiect_id, crima_id)
);

create table SUPRAVEGHERE(
    subiect_id number(5) constraint fk_sub_suprav references SUBIECT(subiect_id),
    agent_id number(5) constraint fk_age_suprav references AGENTT(agent_id),
    data_incepere date,
    constraint pk_suprav primary key(subiect_id, agent_id)
);

create table OCUP_OM(
    subiect_id number(5) constraint fk_sub_ocupom references SUBIECT(subiect_id) on delete cascade,
    ocup_id number(5) constraint fk_ocup_ocupom references OCUPATIE(ocup_id),
    industrie_id number(5) constraint fk_int_ocupom references INDUSTRIE(industrie_id),
    salariu number (5),
    angajator varchar(20),
    constraint pk_ocupom primary key(subiect_id, ocup_id, industrie_id)
);


insert into PUNCT_SUPRAVEGHERE values(secv_id.nextval, 'duba', to_date('01-01-2018', 'dd-mm-yyyy'), 150, 6);
insert into PUNCT_SUPRAVEGHERE values(secv_id.nextval, 'stand limonada', to_date('10-05-2020', 'dd-mm-yyyy'), 500, 4);
insert into PUNCT_SUPRAVEGHERE values(secv_id.nextval, 'fereastra apartament', to_date('15-06-2021', 'dd-mm-yyyy'), 950, 1);
insert into PUNCT_SUPRAVEGHERE values(secv_id.nextval, 'duba', to_date('01-01-2022', 'dd-mm-yyyy'), 50, 5);
insert into PUNCT_SUPRAVEGHERE values(secv_id.nextval, 'masina veche', sysdate-50, 250, 7);

insert into SEDIU values(secv_id.nextval, 'Birou Central', 'Bucuresti', 'Str. Puterii', 432);
insert into SEDIU values(secv_id.nextval, 'Filiala Iasi', 'Iasi', 'Str. Palas', 54);
insert into SEDIU values(secv_id.nextval, 'Subsectie 7', 'Bucuresti', 'Ale. Ascunsa', 1);
insert into SEDIU values(secv_id.nextval, 'Centrul Anti-Mafie', 'Craiova', 'Bd. Sabiilor', 15);
insert into SEDIU values(secv_id.nextval, 'Institutul Visinescu', 'Constanta', 'Str. Inecului', 44);

commit;

insert into AGENTT values (secv_id.nextval ,'Popescu', 'Vasile', 64532, to_date('15-02-2009', 'dd-mm-yyyy'), 10007, 6);
insert into AGENTT values (secv_id.nextval ,'Marinescu', 'Marian', 10000, to_date('16-07-2018', 'dd-mm-yyyy'), 10005, 3);
insert into AGENTT values (secv_id.nextval ,'Enea', 'Robert', 23114, to_date('10-10-2014', 'dd-mm-yyyy'), 10005, 6);
insert into AGENTT values (secv_id.nextval ,'Joacabine', 'Mirel', 23425, to_date('17-11-2016', 'dd-mm-yyyy'), 10008, 5);
insert into AGENTT values (secv_id.nextval ,'Rocadura', 'Artur', 234533, to_date('11-11-2000', 'dd-mm-yyyy'), 10006, 9);

insert into CRIME values(secv_id.nextval, 'terorism', 6, 90000000);
insert into CRIME values(secv_id.nextval, 'inalta tradare', 8, 60500000);
insert into CRIME values(secv_id.nextval, 'spionaj', 7, 80500000);
insert into CRIME values(secv_id.nextval, 'delapidare', 3, 9950000);
insert into CRIME values(secv_id.nextval, 'atac cibernetic', 6, 99999999);

commit;

insert into INDUSTRIE values(secv_id.nextval, 'horeca', '5000025342', 3);
insert into INDUSTRIE values(secv_id.nextval, 'autoturisme', '12573864243', 5);
insert into INDUSTRIE values(secv_id.nextval, 'farmaceutice', '7893543544', 8);
insert into INDUSTRIE values(secv_id.nextval, 'IT', '35000124353', 7);
insert into INDUSTRIE values(secv_id.nextval, 'politica', null, 5);

insert into INTERESE values(secv_id.nextval, 'activitati montane', 2, 1000);
insert into INTERESE values(secv_id.nextval, 'jocuri de noroc', 7, 5000);
insert into INTERESE values(secv_id.nextval, 'gaming', 3, 300);
insert into INTERESE values(secv_id.nextval, 'calatorii spontane', 8, 6000);
insert into INTERESE values(secv_id.nextval, 'petreceri interlopi', 9, 40000);

commit;

insert into SUBIECT values(secv_id.nextval, 10000, 3);
insert into SUBIECT values(secv_id.nextval, 10001, 7);
insert into SUBIECT values(secv_id.nextval, null, 5);
insert into SUBIECT values(secv_id.nextval, 10002, 4);
insert into SUBIECT values(secv_id.nextval, null, 3);
insert into SUBIECT values(secv_id.nextval, null, 7);
insert into SUBIECT values(secv_id.nextval, null, 8);
insert into SUBIECT values(secv_id.nextval, null, 8);
insert into SUBIECT values(secv_id.nextval, 10004, 4);
insert into SUBIECT values(secv_id.nextval, null, 1);
insert into SUBIECT values(secv_id.nextval, null, 3);
insert into SUBIECT values(secv_id.nextval, null, 2);
insert into SUBIECT values(secv_id.nextval, null, 4);
insert into SUBIECT values(secv_id.nextval, 10003, 5);
insert into SUBIECT values(secv_id.nextval, null, 3);

insert into INTERES_OM values (10026, 10034);
insert into INTERES_OM values (10027, 10036);
insert into INTERES_OM values (10026, 10041);
insert into INTERES_OM values (10029, 10041);
insert into INTERES_OM values (10029, 10042);
insert into INTERES_OM values (10025, 10035);
insert into INTERES_OM values (10028, 10032);
insert into INTERES_OM values (10026, 10036);
insert into INTERES_OM values (10029, 10039);
insert into INTERES_OM values (10025, 10043);
insert into INTERES_OM values (10025, 10036);
insert into INTERES_OM values (10027, 10035);
insert into INTERES_OM values (10027, 10043);
commit;

insert into OCUPATIE values(secv_id.nextval, 'motostivuitor', 4000, 1500);
insert into OCUPATIE values(secv_id.nextval, 'inginer', 12000, 3500);
insert into OCUPATIE values(secv_id.nextval, 'chimist', 8000, 2000);
insert into OCUPATIE values(secv_id.nextval, 'programator', 60000, 3500);
insert into OCUPATIE values(secv_id.nextval, 'tester', 5000, 2000);
insert into OCUPATIE values(11000, 'barman', 4000, 1500);


insert into PERSOANA_FIZICA values (10032, 6030116196416, 'Nemtanu', 'Violeta', to_date('16-01-2003', 'dd-mm-yyyy'), 'MZ', '724312');
insert into PERSOANA_FIZICA values (10034, '1940728155764', 'Vasilescu', 'Ion', to_date('28-07-1994', 'dd-mm-yyyy'), 'MX', '483945');
insert into PERSOANA_FIZICA values (10035, '1880109244504', 'Mormon', 'Marius', to_date('09-01-1988', 'dd-mm-yyyy'), 'MZ', '457453');
insert into PERSOANA_FIZICA values (10036, '1870218196401', 'Cormen', 'Vioren', to_date('18-02-1987', 'dd-mm-yyyy'), 'IO', '275421');
insert into PERSOANA_FIZICA values (10039, '2931212053701', 'Magdon', 'Magdalena', to_date('12-12-1993', 'dd-mm-yyyy'), 'VE', '348562');
insert into PERSOANA_FIZICA values (10041, '5000904137459', 'Verestiuc', 'Radu', to_date('04-09-2000', 'dd-mm-yyyy'), 'AU', '124364');
insert into PERSOANA_FIZICA values (10042, '6040406454955', 'Vararu', 'Monica', to_date('16-01-2004', 'dd-mm-yyyy'), 'BU', '854291');
insert into PERSOANA_FIZICA values (10043, '2970707087952', 'Baron', 'Robert', to_date('07-07-1997', 'dd-mm-yyyy'), 'BV', '415261');

insert into PERSOANA_JURIDICA values(10030, 'J22/973/2000', 'RO13611073C', '1243', to_date('05-05-2000', 'dd-mm-yyyy'), '1325531', 'Ion Pavel', 'Trafic de pufarine');
insert into PERSOANA_JURIDICA values(10031, 'J40/1973/2015', 'RO45361325C', '4241', to_date('06-06-2016', 'dd-mm-yyyy'), '325634634', 'Victor Manea', 'Regatul Comertului');
insert into PERSOANA_JURIDICA values(10033, 'J40/1642/2011', 'RO75327543C', '1123', to_date('01-02-2011', 'dd-mm-yyyy'), '21446432', 'Alexandru Babiles', 'Tinutul Shaorma');
insert into PERSOANA_JURIDICA values(10037, 'J21/991/2008', 'RO12345678C', '1234', to_date('01-09-2008', 'dd-mm-yyyy'), '11234456', 'Ion Velcescu', 'Firma ff legala');
insert into PERSOANA_JURIDICA values(10038, 'J11/125/2001', 'RO64262233C', '4321', to_date('06-09-2001', 'dd-mm-yyyy'), '5346374574', 'Vlad Volonce', 'Baieti grei SRL');
insert into PERSOANA_JURIDICA values(10040, 'J40/111/2005', 'RO12775544C', '3221', to_date('02-02-2005', 'dd-mm-yyyy'), '5555555', 'Mircea Simionescu', 'CazinoBarr');
insert into PERSOANA_JURIDICA values(10044, 'J15/125/2020', 'RO11224464C', '123', to_date('12-12-2020', 'dd-mm-yyyy'), '125532', 'Alex Maces', 'Fabrica de barbati');

commit;

insert into SUSPICIUNE_CRIMA values(10037, 10015, to_date('15-07-2018', 'dd-mm-yyyy'), 3);
insert into SUSPICIUNE_CRIMA values(10041, 10018, to_date('19-02-2020', 'dd-mm-yyyy'), 12);
insert into SUSPICIUNE_CRIMA values(10043, 10019, to_date('12-12-2013', 'dd-mm-yyyy'), 2);
insert into SUSPICIUNE_CRIMA values(10035, 10016, to_date('01-05-2016', 'dd-mm-yyyy'), 1);
insert into SUSPICIUNE_CRIMA values(10044, 10018, to_date('02-03-2019', 'dd-mm-yyyy'), 10);
insert into SUSPICIUNE_CRIMA values(10036, 10016, to_date('02-03-2012', 'dd-mm-yyyy'), 2);
insert into SUSPICIUNE_CRIMA values(10040, 10017, to_date('15-06-2008', 'dd-mm-yyyy'), 6);
insert into SUSPICIUNE_CRIMA values(10035, 10018, to_date('28-11-2021', 'dd-mm-yyyy'), 2);
insert into SUSPICIUNE_CRIMA values(10044, 10019, to_date('26-12-2020', 'dd-mm-yyyy'), 8);
insert into SUSPICIUNE_CRIMA values(10037, 10017, to_date('22-11-2019', 'dd-mm-yyyy'), 7);

insert into SUPRAVEGHERE values(10032, 10013, to_date('16-08-2021', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10033, 10010, to_date('19-04-2020', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10044, 10014, to_date('26-01-2021', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10034, 10012, to_date('19-08-2021', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10042, 10010, to_date('16-03-2019', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10044, 10013, to_date('07-12-2019', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10034, 10011, to_date('11-10-2019', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10042, 10014, to_date('06-11-2021', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10031, 10012, to_date('21-09-2021', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10032, 10011, to_date('13-02-2022', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10037, 10013, to_date('07-10-2016', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10038, 10011, to_date('30-06-2015', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10041, 10014, to_date('06-07-2020', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10043, 10012, to_date('21-02-2021', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10036, 10011, to_date('31-07-2020', 'dd-mm-yyyy'));
insert into SUPRAVEGHERE values(10038, 10010, to_date('26-07-2021', 'dd-mm-yyyy'));
commit;

insert into OCUP_OM values (10034, 10045, 10021, 7000, 'Tractoare si lopeti');
insert into OCUP_OM values (10032, 10048, 10024, 15000, 'Vervontis');
insert into OCUP_OM values (10042, 10046, 10020, 3500, 'Mercurian');
insert into OCUP_OM values (10041, 10049, 10022, 6432, 'Babion');
insert into OCUP_OM values (10043, 10047, 10021, 11003, 'Boninu');
insert into OCUP_OM values (10039, 10045, 10020, 5322, 'McOron');
insert into OCUP_OM values (10032, 10046, 10023, 1800, 'Qurons');
insert into OCUP_OM values (10035, 10046, 10024, 2500, 'Baban');
insert into OCUP_OM values (10035, 10047, 10022, 1532, 'Guguc');
insert into OCUP_OM values (10041, 10047, 10022, 3500, 'Lelene');

commit;
