CREATE DATABASE  IF NOT EXISTS `enigma` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `enigma`;
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: enigma
-- ------------------------------------------------------
-- Server version	5.5.31-0+wheezy1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `machine`
--

DROP TABLE IF EXISTS `machine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `machine` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL COMMENT 'Machine name\n',
  `steckerboard` enum('NO','YES') NOT NULL DEFAULT 'YES' COMMENT 'Does the machine have a steckerboard\n',
  `rotorcount` int(11) NOT NULL DEFAULT '0' COMMENT 'Number of rotors in machine',
  `entrylist` varchar(250) DEFAULT NULL,
  `rotorlist` varchar(250) DEFAULT NULL,
  `reflectorlist` varchar(250) DEFAULT NULL,
  `alphabetid` int(11) NOT NULL COMMENT 'key of alphabet in alphabet table',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_unique_machinename` (`name`),
  KEY `fk_machine_alphabetid` (`alphabetid`),
  CONSTRAINT `fk_machine_alphabetid` FOREIGN KEY (`alphabetid`) REFERENCES `alphabet` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1 COMMENT='Enigma machine definitions';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `machine`
--

LOCK TABLES `machine` WRITE;
/*!40000 ALTER TABLE `machine` DISABLE KEYS */;
INSERT INTO `machine` VALUES (1,'Naval','YES',4,'ENTRY','I,II,III','B,C',1),(2,'Wermacht','YES',3,'ENTRY','I,II,III,IV','B,C',4),(3,'Luftwaffe','YES',3,'ENTRY','I,II,III,IV,V','B,C',3);
/*!40000 ALTER TABLE `machine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `alphabet`
--

DROP TABLE IF EXISTS `alphabet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alphabet` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'primary key',
  `name` varchar(100) NOT NULL COMMENT 'unique name for alphabet',
  `alphabet` varchar(250) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_unique_alphabet_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1 COMMENT='alphabets that can be used by enigma components';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `alphabet`
--

LOCK TABLES `alphabet` WRITE;
/*!40000 ALTER TABLE `alphabet` DISABLE KEYS */;
INSERT INTO `alphabet` VALUES (1,'default','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),(2,'test3','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),(3,'test2','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),(4,'standard26','ABCDEFGHIJKLMNOPQRSTUVWXYZ');
/*!40000 ALTER TABLE `alphabet` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `report`
--

DROP TABLE IF EXISTS `report`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `report` (
  `report_id` int(11) NOT NULL,
  `report_name` text,
  `report_descrip` text NOT NULL,
  `report_grade` int(11) NOT NULL DEFAULT '0',
  `report_source` text,
  PRIMARY KEY (`report_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `report`
--

LOCK TABLES `report` WRITE;
/*!40000 ALTER TABLE `report` DISABLE KEYS */;
INSERT INTO `report` VALUES (0,'aaa report_name aaa','ccc report_description ccc\nccc report_description ccc\nccc report_description ccc',0,'<!DOCTYPE openRPTDef>\n<report>\n <title>bbb report_title bbb</title>\n <name>aaa report_name aaa</name>\n <description>ccc report_description ccc\nccc report_description ccc\nccc report_description ccc</description>\n <size>Letter</size>\n <portrait/>\n <topmargin>100</topmargin>\n <bottommargin>100</bottommargin>\n <rightmargin>100</rightmargin>\n <leftmargin>100</leftmargin>\n <querysource>\n  <name>rotor</name>\n  <sql>SELECT id, name, alphabetid, type, pinright, notches \nfrom rotor;</sql>\n </querysource>\n <colordef>\n  <name>black</name>\n  <red>0</red>\n  <green>0</green>\n  <blue>0</blue>\n </colordef>\n <colordef>\n  <name>red</name>\n  <red>0</red>\n  <green>0</green>\n  <blue>0</blue>\n </colordef>\n <rpthead>\n  <height>100</height>\n  <label>\n   <rect>\n    <x>38</x>\n    <y>25.5</y>\n    <width>100</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <left/>\n   <top/>\n   <string>Report Header</string>\n  </label>\n </rpthead>\n <pghead>\n  <height>45.7992</height>\n  <label>\n   <rect>\n    <x>443</x>\n    <y>8.36</y>\n    <width>45</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <left/>\n   <top/>\n   <string>Page</string>\n  </label>\n  <field>\n   <rect>\n    <x>592</x>\n    <y>8.53</y>\n    <width>45</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <left/>\n   <top/>\n   <data>\n    <query>Context Query</query>\n    <column>page_count</column>\n   </data>\n  </field>\n  <field>\n   <rect>\n    <x>495.932</x>\n    <y>7.23457</y>\n    <width>50</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <right/>\n   <top/>\n   <data>\n    <query>Context Query</query>\n    <column>page_number</column>\n   </data>\n  </field>\n  <label>\n   <rect>\n    <x>556.213</x>\n    <y>8.62243</y>\n    <width>25</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <hcenter/>\n   <top/>\n   <string>/</string>\n  </label>\n  <label>\n   <rect>\n    <x>36.1491</x>\n    <y>7.24721</y>\n    <width>100</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <left/>\n   <top/>\n   <string>Page Header</string>\n  </label>\n </pghead>\n <section>\n  <name>detail</name>\n  <detail>\n   <key>\n    <query>rotor</query>\n   </key>\n   <height>77.026</height>\n   <label>\n    <rect>\n     <x>71.9755</x>\n     <y>6.8435</y>\n     <width>100</width>\n     <height>25</height>\n    </rect>\n    <font>\n     <face>Sans Serif</face>\n     <size>10</size>\n     <weight>normal</weight>\n    </font>\n    <left/>\n    <top/>\n    <string>Detail Line</string>\n   </label>\n   <field>\n    <rect>\n     <x>318.375</x>\n     <y>4.14164</y>\n     <width>183.903</width>\n     <height>25</height>\n    </rect>\n    <font>\n     <face>Sans Serif</face>\n     <size>10</size>\n     <weight>normal</weight>\n    </font>\n    <left/>\n    <top/>\n    <data>\n     <query>rotor</query>\n     <column>pinright</column>\n    </data>\n   </field>\n   <field>\n    <rect>\n     <x>192</x>\n     <y>5.5</y>\n     <width>100</width>\n     <height>25</height>\n    </rect>\n    <font>\n     <face>Sans Serif</face>\n     <size>10</size>\n     <weight>normal</weight>\n    </font>\n    <left/>\n    <top/>\n    <data>\n     <query>rotor</query>\n     <column>id</column>\n    </data>\n   </field>\n  </detail>\n </section>\n <pgfoot>\n  <height>100</height>\n  <label>\n   <rect>\n    <x>30.2</x>\n    <y>32.6</y>\n    <width>100</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <left/>\n   <top/>\n   <string>Page Footer</string>\n  </label>\n </pgfoot>\n <rptfoot>\n  <height>100</height>\n  <label>\n   <rect>\n    <x>30.2</x>\n    <y>18</y>\n    <width>100</width>\n    <height>25</height>\n   </rect>\n   <font>\n    <face>Sans Serif</face>\n    <size>10</size>\n    <weight>normal</weight>\n   </font>\n   <left/>\n   <top/>\n   <string>Report Footer</string>\n  </label>\n </rptfoot>\n</report>\n');
/*!40000 ALTER TABLE `report` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `machinedefn`
--

DROP TABLE IF EXISTS `machinedefn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `machinedefn` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `machineid` int(11) NOT NULL,
  `rotorid` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_machineid_rotorid` (`machineid`,`rotorid`),
  KEY `fk_machineid` (`machineid`),
  KEY `fk_rotorid` (`rotorid`),
  CONSTRAINT `fk_machineid` FOREIGN KEY (`machineid`) REFERENCES `machine` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_rotorid` FOREIGN KEY (`rotorid`) REFERENCES `rotor` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1 COMMENT='Enigma Machine Definition';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `machinedefn`
--

LOCK TABLES `machinedefn` WRITE;
/*!40000 ALTER TABLE `machinedefn` DISABLE KEYS */;
INSERT INTO `machinedefn` VALUES (1,2,1),(2,2,2),(3,2,3),(4,2,4),(5,2,12);
/*!40000 ALTER TABLE `machinedefn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rotor`
--

DROP TABLE IF EXISTS `rotor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rotor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL COMMENT 'rotor name',
  `alphabetid` int(11) NOT NULL,
  `type` enum('ENTRY','ROTOR','REFLECTOR','THIN') NOT NULL COMMENT 'Type of Rotor  - A Greek Rotor is a thin rotor is the fourth rotor as used in the Naval Enigma\n',
  `pinright` varchar(150) NOT NULL COMMENT 'Right hand pin wiring\n',
  `notches` varchar(50) DEFAULT NULL COMMENT 'Rotor Notches\n',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_unique_rotorname` (`name`),
  KEY `fk_rotor_alphabetid` (`alphabetid`),
  CONSTRAINT `fk_rotor_alphabetid` FOREIGN KEY (`alphabetid`) REFERENCES `alphabet` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=latin1 COMMENT='rotor definitions';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rotor`
--

LOCK TABLES `rotor` WRITE;
/*!40000 ALTER TABLE `rotor` DISABLE KEYS */;
INSERT INTO `rotor` VALUES (1,'ENTRY',1,'ENTRY','ABCDEFGHIJKLMNOPQRSTUVWXYZ',''),(2,'I',1,'ROTOR','EKMFLGDQVZNTOWYHXUSPAIBRCJ','Q'),(3,'II',1,'ROTOR','AJDKSIRUXBLHWTMCQGZNPYFVOE','E'),(4,'III',1,'ROTOR','BDFHJLCPRTXVZNYEIWGAKMUSQO','V'),(5,'IV',1,'ROTOR','ESOVPZJAYQUIRHXLNFTGKDCMWB','J'),(6,'V',1,'ROTOR','VZBRGITYUPSDNHLXAWMJQOFECK','Z'),(7,'VI',1,'ROTOR','JPGVOUMFYQBENHZRDKASXLICTW','ZM'),(8,'VII',1,'ROTOR','NZJHGRCXMYSWBOUFAIVLPEKQDT','ZM'),(9,'VIII',1,'ROTOR','FKQHTLXOCBJSPDZRAMEWNIUYGV','ZM'),(10,'BETA',1,'ROTOR','LEYJVCNIXWPBQMDRTAKZGFUHOS',''),(11,'GAMMA',1,'ROTOR','FSOKANUERHMBTIYCWLQPZXVGJD',''),(12,'B',1,'REFLECTOR','YRUHQSLDPXNGOKMIEBFZCWVJAT',''),(13,'C',1,'REFLECTOR','FVPJIAOYEDRZXWGCTKUQSBNMHL',''),(14,'B DUNN',1,'REFLECTOR','ENKQAUYWJICOPBLMDXZVFTHRGS',''),(15,'C DUNN',1,'REFLECTOR','RDOBJNTKVEHMLFCWZAXGYIPSUQ',''),(16,'REFLECTOR',1,'REFLECTOR','ABCDEFGHIJKLMNOPQRSTUVWXYZ',''),(17,'ROTOR',1,'ROTOR','ABCDEFGHIJKLMNOPQRSTUVWXYZ','E');
/*!40000 ALTER TABLE `rotor` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-05-17 18:47:44
