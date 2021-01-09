use firstdb;

DROP TABLE kkkadry;
CREATE TABLE `kkkadry` (
    `KodStudenta` tinyint(4) DEFAULT NULL,
    `Pol` varchar(10) DEFAULT NULL,
    `Familia` varchar(10) DEFAULT NULL,
    `Ima` varchar(9) DEFAULT NULL,
    `Obcestvo` varchar(9) DEFAULT NULL,
    `DataRozdenia` varchar(19) DEFAULT NULL,
    `NomerUcGruppy` smallint(6) DEFAULT NULL,
    `Grazdanstvo` varchar(6) DEFAULT NULL
);

INSERT INTO `kkkadry` VALUES (1,'muzskoy','Pushkin','Aleksandr','Sergeich','1999-05-10 00:00:00',112,'Rossia');
INSERT INTO `kkkadry` VALUES (2,'Korotyskin','Vakeriy','Aleksandr','Sergeich','1999-05-12 00:00:00',112,'Kitay');
INSERT INTO `kkkadry` VALUES (3,'muzskoy','Shishkin','Aleksandr','Sergeich','1999-05-15 00:00:00',112,'Rossia');

SELECT * FROM kkkadry;
