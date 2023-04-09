-- LDD (langage de définition de données)

-- Voir aussi : https://www.db4free.net/phpMyAdmin/

DROP DATABASE IF EXISTS `ecoclassroom`;

CREATE DATABASE IF NOT EXISTS `ecoclassroom` CHARACTER SET utf8;

--
-- Base de données : `ecoclassroom`
--

USE ecoclassroom;

DROP TABLE IF EXISTS SeuilsAlerte;
DROP TABLE IF EXISTS MesureCo2;
DROP TABLE IF EXISTS MesureLuminosite;
DROP TABLE IF EXISTS MesureHumidite;
DROP TABLE IF EXISTS MesureTemperature;
DROP TABLE IF EXISTS BrokerMQTT;
DROP TABLE IF EXISTS IndiceQualiteAir;
DROP TABLE IF EXISTS IndiceConfinement;
DROP TABLE IF EXISTS IndiceInconfortIADI;
DROP TABLE IF EXISTS IndiceConfortTHI;
DROP TABLE IF EXISTS Salle;

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `IndiceConfortTHI` (
	`idIndiceConfortTHI`	int NOT NULL,
	`libelle`	varchar(255)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `IndiceConfortTHI`
  ADD PRIMARY KEY (`idIndiceConfortTHI`);

INSERT INTO IndiceConfortTHI(idIndiceConfortTHI,libelle) VALUES
(-4,'inconnu'),
(-3,'froid'),
(-2,'frais'),
(-1,'légèrement frais'),
(0,'neutre'),
(1,'légèrement tiède'),
(2,'tiède'),
(3,'chaud');

CREATE TABLE IF NOT EXISTS `IndiceInconfortIADI` (
	`idIndiceInconfortIADI`	int NOT NULL,
	`libelle`	varchar(255)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `IndiceInconfortIADI`
  ADD PRIMARY KEY (`idIndiceInconfortIADI`);

INSERT INTO IndiceInconfortIADI(idIndiceInconfortIADI,libelle) VALUES
(0,'aucun'),
(1,'gêne'),
(2,'mal être'),
(3,'inconfort'),
(4,'stress intense'),
(5,'urgence médicale');

CREATE TABLE IF NOT EXISTS `IndiceConfinement` (
	`idIndiceConfinement`	int NOT NULL,
	`libelle`	varchar(255)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `IndiceConfinement`
  ADD PRIMARY KEY (`idIndiceConfinement`);

INSERT INTO IndiceConfinement(idIndiceConfinement,libelle) VALUES
(0, 'nul'),
(1, 'faible'),
(2, 'moyen'),
(3, 'élevé'),
(4, 'très élevé'),
(5, 'extrême');

CREATE TABLE IF NOT EXISTS `IndiceQualiteAir` (
	`idIndiceQualiteAir`	int NOT NULL,
	`libelle`	varchar(255)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `IndiceQualiteAir`
  ADD PRIMARY KEY (`idIndiceQualiteAir`);

INSERT INTO IndiceQualiteAir(idIndiceQualiteAir,libelle) VALUES
(0,'inconnu'),
(1,'excellent'),
(2,'très bien'),
(3,'modéré'),
(4,'mauvais'),
(5,'très mauvais'),
(6,'sévère');

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `Salle` (
	`idSalle`	int NOT NULL AUTO_INCREMENT PRIMARY KEY,
	`nom`	varchar(32),
	`description`	varchar(255),
	`superficie`	int DEFAULT '0',
	`idIndiceConfortTHI`	int DEFAULT '-4',
    `idIndiceInconfortIADI`	int DEFAULT '0',
	`idIndiceQualiteAir`	int DEFAULT '0',
    `idIndiceConfinement`	int DEFAULT '0',
	`etatFenetres`	int DEFAULT '0',
	`etatLumieres`	int DEFAULT '0',
	`estOccupe`	int DEFAULT '0',
	`estFavori`	int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Salle`
  ADD UNIQUE KEY `nom` (`nom`);

-- ALTER TABLE `Salle` CHANGE `idSalle` `idSalle` INT NOT NULL AUTO_INCREMENT, add PRIMARY KEY (`idSalle`); 

ALTER TABLE `Salle`
  ADD CONSTRAINT `Salle_fk_1` FOREIGN KEY (`idIndiceConfortTHI`) REFERENCES `IndiceConfortTHI` (`idIndiceConfortTHI`) ON DELETE CASCADE,
  ADD CONSTRAINT `Salle_fk_2` FOREIGN KEY (`idIndiceInconfortIADI`) REFERENCES `IndiceInconfortIADI` (`idIndiceInconfortIADI`) ON DELETE CASCADE,
  ADD CONSTRAINT `Salle_fk_3` FOREIGN KEY (`idIndiceQualiteAir`) REFERENCES `IndiceQualiteAir` (`idIndiceQualiteAir`) ON DELETE CASCADE,
  ADD CONSTRAINT `Salle_fk_4` FOREIGN KEY (`idIndiceConfinement`) REFERENCES `IndiceConfinement` (`idIndiceConfinement`) ON DELETE CASCADE;

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `BrokerMQTT` (
	`idBrokerMQTT`	int,
	`hostname`	varchar(255) NOT NULL,
	`port`	int NOT NULL DEFAULT '1883',
	`username`	varchar(64) DEFAULT NULL,
	`password`	varchar(64) DEFAULT NULL,
	`estActif`	int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `BrokerMQTT`
  ADD PRIMARY KEY (`idBrokerMQTT`);

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `MesureTemperature` (
	`idMesureTemperature`	int AUTO_INCREMENT PRIMARY KEY,
	`idSalle`	int NOT NULL,
	`temperature`	DECIMAL(3, 1) NOT NULL,
	`horodatage`	DATETIME NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `MesureTemperature`
  ADD UNIQUE KEY `horodatage` (`horodatage`),
  ADD KEY `MesureTemperature_fk_1` (`idSalle`);

ALTER TABLE `MesureTemperature`
  ADD CONSTRAINT `MesureTemperature_fk_1` FOREIGN KEY (`idSalle`) REFERENCES `Salle` (`idSalle`) ON DELETE CASCADE;

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `MesureHumidite` (
	`idMesureHumidite`	int AUTO_INCREMENT PRIMARY KEY,
	`idSalle`	int NOT NULL,
	`humidite`	TINYINT UNSIGNED NOT NULL,
	`horodatage`	DATETIME NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `MesureHumidite`
  ADD UNIQUE KEY `horodatage` (`horodatage`),
  ADD KEY `MesureHumidite_fk_1` (`idSalle`);

ALTER TABLE `MesureHumidite`
  ADD CONSTRAINT `MesureHumidite_fk_1` FOREIGN KEY (`idSalle`) REFERENCES `Salle` (`idSalle`) ON DELETE CASCADE;

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `MesureLuminosite` (
	`idMesureLuminosite`	int AUTO_INCREMENT PRIMARY KEY,
	`idSalle`	int NOT NULL,
	`luminosite`	SMALLINT UNSIGNED NOT NULL,
	`horodatage`	DATETIME NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `MesureLuminosite`
  ADD UNIQUE KEY `horodatage` (`horodatage`),
  ADD KEY `MesureLuminosite_fk_1` (`idSalle`);

ALTER TABLE `MesureLuminosite`
  ADD CONSTRAINT `MesureLuminosite_fk_1` FOREIGN KEY (`idSalle`) REFERENCES `Salle` (`idSalle`) ON DELETE CASCADE;

-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `MesureCo2` (
	`idMesureCo2`	int AUTO_INCREMENT PRIMARY KEY,
	`idSalle`	int NOT NULL,
	`co2`	SMALLINT UNSIGNED NOT NULL,
	`horodatage`	DATETIME NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `MesureCo2`
  ADD UNIQUE KEY `horodatage` (`horodatage`),
  ADD KEY `MesureCo2_fk_1` (`idSalle`);

ALTER TABLE `MesureCo2`
  ADD CONSTRAINT `MesureCo2_fk_1` FOREIGN KEY (`idSalle`) REFERENCES `Salle` (`idSalle`) ON DELETE CASCADE;

-- --------------------------------------------------------

-- Pour chaque salle ou pour toutes ? 

CREATE TABLE IF NOT EXISTS `SeuilsAlerte` (
	`idSalle`	int NOT NULL,
	`temperatureMin`	double,
	`temperatureMax`	double,
	`luminositeMin`	int,
	`luminositeMax`	int,
	`humiditeMin`	int,
	`humiditeMax`	int,
	`co2Min`	int,
	`co2Max`	int
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `SeuilsAlerte`
  ADD PRIMARY KEY (`idSalle`);

ALTER TABLE `SeuilsAlerte`
  ADD CONSTRAINT `SeuilsAlerte_fk_1` FOREIGN KEY (`idSalle`) REFERENCES `Salle` (`idSalle`) ON DELETE CASCADE;

-- --------------------------------------------------------
