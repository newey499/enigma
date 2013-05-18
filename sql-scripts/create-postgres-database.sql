-- ==============================
--
--
-- create-postgres-database.sql
--
--
-- ==============================
-- Create Database
-- ==============================

-- ========================================================
-- For Postgresql don't create a database - assume one has
-- been created for the current user and create the enigma 
-- schema in the user database.
-- ========================================================
--drop database if exists enigma CASCADE;
--CREATE DATABASE  enigma; 

DROP schema if exists enigma
CREATE schema enigma;

SET search_path TO enigma, public;

-- ===================================================================

drop table IF EXISTS alphabet CASCADE;
CREATE TABLE alphabet
(
  id SERIAL PRIMARY KEY,
  name varchar(100) NOT NULL,
  alphabet varchar(250) NOT NULL
);
CREATE UNIQUE INDEX alphabet_name_unique ON alphabet(name);

-- ===================================================================

DROP TYPE rotor_type CASCADE;
CREATE TYPE rotor_type AS ENUM('ENTRY','ROTOR','REFLECTOR','THIN');

DROP TABLE IF EXISTS rotor CASCADE;
CREATE TABLE rotor (
  id SERIAL PRIMARY KEY,
  name varchar(50) NOT NULL,
  alphabetid int NOT NULL references alphabet(id),
  type rotor_type NOT NULL,
  pinright varchar(150) NOT NULL,
  notches varchar(50) DEFAULT NULL
);
CREATE UNIQUE INDEX rotor_name_unique ON rotor(name);

-- ===================================================================

DROP TYPE steckerboard_type CASCADE;
CREATE TYPE steckerboard_type AS ENUM('NO','YES');

DROP TABLE IF EXISTS machine CASCADE;
CREATE TABLE machine
(
  id SERIAL PRIMARY KEY,
  name varchar(50) NOT NULL,
  steckerboard steckerboard_type NOT NULL DEFAULT 'YES' ,
  rotorcount int NOT NULL DEFAULT 0,
  entrylist varchar(250) DEFAULT NULL,
  rotorlist varchar(250) DEFAULT NULL,
  reflectorlist varchar(250) DEFAULT NULL,
  alphabetid int NOT NULL REFERENCES alphabet(id)
);
CREATE UNIQUE INDEX machine_name_unique on machine(name);

-- ===================================================================

DROP TABLE IF EXISTS machinedefn CASCADE;
CREATE TABLE machinedefn 
(
  id SERIAL PRIMARY KEY,
  machineid int NOT NULL REFERENCES machine(id) ON DELETE CASCADE ON UPDATE CASCADE,
  rotorid int NOT NULL REFERENCES rotor(id) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE UNIQUE INDEX machinedefn_machineid_rotorid_unique on machinedefn(machineid, rotorid);


-- ==============================
-- Insert initial data
-- ==============================

-- ===================================================================

INSERT INTO alphabet(name, alphabet) 
VALUES 
('default','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),
('test3','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),
('test2','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),
('standard26','ABCDEFGHIJKLMNOPQRSTUVWXYZ');

-- ===================================================================

INSERT INTO rotor(name, alphabetid, type, pinright, notches) 
VALUES 
('ENTRY',1,'ENTRY','ABCDEFGHIJKLMNOPQRSTUVWXYZ',''),
('I',1,'ROTOR','EKMFLGDQVZNTOWYHXUSPAIBRCJ','Q'),
('II',1,'ROTOR','AJDKSIRUXBLHWTMCQGZNPYFVOE','E'),
('III',1,'ROTOR','BDFHJLCPRTXVZNYEIWGAKMUSQO','V'),
('IV',1,'ROTOR','ESOVPZJAYQUIRHXLNFTGKDCMWB','J'),
('V',1,'ROTOR','VZBRGITYUPSDNHLXAWMJQOFECK','Z'),
('VI',1,'ROTOR','JPGVOUMFYQBENHZRDKASXLICTW','ZM'),
('VII',1,'ROTOR','NZJHGRCXMYSWBOUFAIVLPEKQDT','ZM'),('VIII',1,'ROTOR','FKQHTLXOCBJSPDZRAMEWNIUYGV','ZM'),
('BETA',1,'ROTOR','LEYJVCNIXWPBQMDRTAKZGFUHOS',''),
('GAMMA',1,'ROTOR','FSOKANUERHMBTIYCWLQPZXVGJD',''),
('B',1,'REFLECTOR','YRUHQSLDPXNGOKMIEBFZCWVJAT',''),
('C',1,'REFLECTOR','FVPJIAOYEDRZXWGCTKUQSBNMHL',''),
('B DUNN',1,'REFLECTOR','ENKQAUYWJICOPBLMDXZVFTHRGS',''),
('C DUNN',1,'REFLECTOR','RDOBJNTKVEHMLFCWZAXGYIPSUQ',''),('REFLECTOR',1,'REFLECTOR','ABCDEFGHIJKLMNOPQRSTUVWXYZ',''),('ROTOR',1,'ROTOR','ABCDEFGHIJKLMNOPQRSTUVWXYZ','E');

-- ===================================================================

INSERT INTO machine(name, steckerboard, rotorcount,
                    entrylist, rotorlist, reflectorlist, alphabetid)
VALUES 
('Naval','YES',4,'ENTRY','I,II,III','B,C',1),
('Wermacht','YES',3,'ENTRY','I,II,III,IV','B,C',4),('Luftwaffe','YES',3,'ENTRY','I,II,III,IV,V','B,C',3);

-- ===================================================================

INSERT INTO machinedefn(machineid, rotorid) 
VALUES 
(2,1),
(2,2),
(2,3),
(2,4),
(2,12);


