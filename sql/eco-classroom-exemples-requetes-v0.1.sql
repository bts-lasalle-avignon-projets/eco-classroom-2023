-- Exemples de requêtes SQL

-- Nombre de salles

SELECT COUNT(*) AS NbSalles FROM Salle;

-- Liste des indices de confort THI

SELECT idIndiceConfortTHI,libelle FROM IndiceConfortTHI
WHERE idIndiceConfortTHI >= '-3';

-- Liste des indices de qualité d'air

SELECT * FROM IndiceQualiteAir
WHERE idIndiceQualiteAir > '0';

-- Liste des salles

SELECT * FROM Salle;

SELECT Salle.nom,IndiceConfortTHI.libelle,IndiceQualiteAir.libelle FROM Salle
INNER JOIN IndiceConfortTHI ON IndiceConfortTHI.idIndiceConfortTHI=Salle.idIndiceConfortTHI
INNER JOIN IndiceQualiteAir ON IndiceQualiteAir.idIndiceQualiteAir=Salle.idIndiceQualiteAir;

-- Liste des mesures

SELECT * FROM MesureCo2;

-- récupérer les 5 dernières mesures de CO2 :

SELECT * FROM (SELECT * FROM MesureCo2 ORDER BY horodatage DESC LIMIT 5) tmp ORDER BY horodatage ASC LIMIT 5
INNER JOIN Salle ON MesureCo2.idSalle=Salle.idSalle;

-- récupérer les mesures de température d'une salle :

SELECT * FROM MesureTemperature
INNER JOIN Salle ON MesureTemperature.idSalle=Salle.idSalle
WHERE Salle.idSalle='1';

-- récupérer la dernière mesure d'humidité avec l’horodatage sous la forme d’un TIMESTAMP :

SELECT UNIX_TIMESTAMP(horodatage) as timestamp, humidite FROM MesureHumidite WHERE horodatage IN (SELECT max(horodatage) FROM MesureHumidite WHERE MesureHumidite.idSalle='1')

---- Modifier un état d'une salle

UPDATE Salle SET estOccupe='1' WHERE idSalle='1';

